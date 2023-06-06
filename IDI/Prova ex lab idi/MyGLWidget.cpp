// MyGLWidget.cpp
#include "MyGLWidget.h"
#include <iostream>
#include <stdio.h>

#define printOpenGLError() printOglError(__FILE__, __LINE__)
#define CHECK() printOglError(__FILE__, __LINE__,__FUNCTION__)
#define DEBUG() std::cout << __FILE__ << " " << __LINE__ << " " << __FUNCTION__ << std::endl;

int MyGLWidget::printOglError(const char file[], int line, const char func[]) 
{
    GLenum glErr;
    int    retCode = 0;

    glErr = glGetError();
    const char * error = 0;
    switch (glErr)
    {
        case 0x0500:
            error = "GL_INVALID_ENUM";
            break;
        case 0x501:
            error = "GL_INVALID_VALUE";
            break;
        case 0x502: 
            error = "GL_INVALID_OPERATION";
            break;
        case 0x503:
            error = "GL_STACK_OVERFLOW";
            break;
        case 0x504:
            error = "GL_STACK_UNDERFLOW";
            break;
        case 0x505:
            error = "GL_OUT_OF_MEMORY";
            break;
        default:
            error = "unknown error!";
    }
    if (glErr != GL_NO_ERROR)
    {
        printf("glError in file %s @ line %d: %s function: %s\n",
                             file, line, error, func);
        retCode = 1;
    }
    return retCode;
}

MyGLWidget::~MyGLWidget() {
}

void MyGLWidget::initializeGL() 
{
  ExamGLWidget::initializeGL();
  emit iniButton();
}

void MyGLWidget::resizeGL(int w, int h)
{
  #ifdef __APPLE__
  // Aquest codi és necessari únicament per a MACs amb pantalla retina.
  GLint vp[4];
  glGetIntegerv (GL_VIEWPORT, vp);
  ample = vp[2];
  alt = vp[3];
#else
  ample = w;
  alt = h;
#endif

  ra = float(ample)/float(alt);

  if (ra < 1) {
    float fov2  = atan(tan(M_PI/3.0) / ra);
    fov = fov2;
  }
  else {
    fov = float(M_PI/3.0);
  }

  projectTransform();
}

void MyGLWidget::paintGL ()   // Mètode que has de modificar
{
  // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);
  
  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // Pintem el terra
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  // Pintem el Patricio
  if (not borraPat) {
    glBindVertexArray (VAO_Patr);
    modelTransformPatricio ();
    glDrawArrays(GL_TRIANGLES, 0, patr.faces().size()*3);
  }
  
  // Pintem el cub
  if (borraPat) {
    for (int i = 0; i < 3; ++i) {
      glBindVertexArray(VAO_Cub);
      modelTransformCub (2.0+0.5*i, 2*M_PI/3*(i+iteraCapses));
      glDrawArrays(GL_TRIANGLES, 0, 36);
    }
  }

  glBindVertexArray(0);
}

void MyGLWidget::modelTransformCub (float escala, float angle) 
{
  TG = glm::mat4(1.f);
  TG = glm::rotate(TG, angle, glm::vec3(0,1,0));
  TG = glm::translate(TG, glm::vec3(5,0,0));
  TG = glm::scale(TG, glm::vec3(2*escala, 2*escala, 2*escala));
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformPatricio ()    // Mètode que has de modificar
{
  TG = glm::mat4(1.f);
  TG = glm::rotate(TG, float(2*M_PI/3*(iteraPat + iteraCapses)), glm::vec3(0,1,0));
  TG = glm::translate(TG, glm::vec3(5,0,0));
  TG = glm::rotate(TG, -float(M_PI/2), glm::vec3(1,0,0));
  TG = glm::scale(TG, glm::vec3 (2*escala, 2*escala, 2*escala));
  TG = glm::translate(TG, -centreBasePat);
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::viewTransform ()    // Mètode que has de modificar
{
  if (!camPlanta)
    ExamGLWidget::viewTransform();
  else
  {
    // glm::lookAt (OBS, VRP, UP)
    glm::mat4 View = glm::lookAt(glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &View[0][0]);
  }
}

void MyGLWidget::projectTransform ()
{
  if (!camPlanta)
    ExamGLWidget::projectTransform();
  else
  {
    //glm::ortho (left, rigth, bottom, top, znear, zfar)
    glm::mat4 Proj;
    if (ra > 1) Proj = glm::ortho(-10.0f*ra, 10.0f*ra, -10.0f, 10.0f, 1.0f, 15.0f);
    else Proj = glm::ortho(-10.0f, 10.0f, -10.0f/ra, 10.0f/ra, 1.0f, 15.0f);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
  }
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_V: {
    borraPat = not borraPat;
    break;
	}
  case Qt::Key_1: {
      iteraPat = 0;
      emit modCapsa0();
      update();
    break;
	}
  case Qt::Key_2: {
      iteraPat = 1;
      emit modCapsa1();
      update();
    break;
	}
  case Qt::Key_3: {
      iteraPat = 2;
      emit modCapsa2();
      update();
    break;
	}
  case Qt::Key_F: {
      if (groc) colFoc = glm::vec3(1,1,0);
      else colFoc = glm::vec3(1,1,1);
      
      groc =  not groc;
      enviaColFocus();
    break;
	}
  case Qt::Key_C: {
      camPlanta = not camPlanta;
      viewTransform();
      projectTransform();
      if (camPlanta) emit modCam1();
      else emit modCam();
      update();
    break;
	}
  case Qt::Key_Right: {
      iteraCapses = (++iteraCapses)%3;
    break;
	}
  case Qt::Key_Left: {
      iteraCapses = (--iteraCapses)%3;
    break;
	}
  case Qt::Key_R: {
      initializeGL();
      camPlanta = false;
      viewTransform();
      projectTransform();
      
      iteraPat = 0;
      iteraCapses = 0;
      
      colFoc = glm::vec3(1.0f ,1.0f ,1.0f);
      groc = true;
      borraPat = true;
   
      enviaColFocus();
      update();
    break;
	}
  default: ExamGLWidget::keyPressEvent(event); break;
  }
  update();
}

void MyGLWidget::Capsa1() 
{
   iteraPat = 0;
   update();
}

void MyGLWidget::Capsa2() 
{
   iteraPat = 1;
   update();
}

void MyGLWidget::Capsa3() 
{
   iteraPat = 2;
   update();
}

void MyGLWidget::Pers()
{
  makeCurrent();
  camPlanta = false;
  viewTransform();
  projectTransform();
  update();
}

void MyGLWidget::Orto()
{
  makeCurrent();
  camPlanta = true; 
  viewTransform();
  projectTransform();
  update();
}

