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


void MyGLWidget::initializeGL() {
    LL2GLWidget::initializeGL();
    iniCamera();
    iniEscena();
    iniCamera2();
    carregaShaders();
    rota_cam = 1.0;
    cam2 = false;
    colR = false;
}

void MyGLWidget::resizeGL(int width, int height) {
    LL2GLWidget::resizeGL(width, height);
    raw = float(width)/float(height);
    if (raw < 1) {
        float alfaNou = atan(tan(alfa) / raw);
        fov = 2*alfaNou;
    }
    else {
        fov2 = 2*alfa;
    }
   
}

void MyGLWidget::paintGL() {
  glm::vec3 filt(1.0f);
  glUniform3fv(verde, 1, &filt[0]);

  glm::vec3 invisible(0.0f);
  glUniform3fv(verdR, 1, &invisible[0]);

     // descomentar per canviar paràmetres
  glViewport (0, 0, ample, alt);

  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  projectTransform();
  viewTransform();  
  // Rick
  if (colR) {
    invisible = glm::vec3(0,0.7,0);
    glUniform3fv(verdR, 1, &invisible[0]);
  }
  glBindVertexArray (VAO_models[RICK]);
  RickTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[RICK].faces().size()*3);

  invisible = glm::vec3(0,0,0);
  glUniform3fv(verdR, 1, &invisible[0]);
  
  // Morty
  glBindVertexArray (VAO_models[MORTY]);
  MortyTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[MORTY].faces().size()*3);
  
  // VideoCamera
  glBindVertexArray (VAO_models[VIDEOCAMERA]);
  VideoCameraTransform();
  glDrawArrays(GL_TRIANGLES, 0, models[VIDEOCAMERA].faces().size()*3);  
  
  // Terra
  glBindVertexArray (VAO_Terra);
  identTransform();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  // Paret
  ParetTransform();
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

  if (cam2) { 
    filt = glm::vec3(0, 1, 0);
    glUniform3fv(verde, 1, &filt[0]);
    glViewport (3*ample/4, 3*alt/4, ample/4, alt/4);

    projectTransform2();
    viewTransform2();
    // Rick
    if (colR) {
        invisible = glm::vec3(0,0.7,0);
        glUniform3fv(verdR, 1, &invisible[0]);
    }
    glBindVertexArray (VAO_models[RICK]);
    RickTransform();
    glDrawArrays(GL_TRIANGLES, 0, models[RICK].faces().size()*3);

    invisible = glm::vec3(0,0,0);
    glUniform3fv(verdR, 1, &invisible[0]);

    // Morty
    glBindVertexArray (VAO_models[MORTY]);
    MortyTransform();
    glDrawArrays(GL_TRIANGLES, 0, models[MORTY].faces().size()*3);
    
    // VideoCamera
    glBindVertexArray (VAO_models[VIDEOCAMERA]);
    VideoCameraTransform();
    glDrawArrays(GL_TRIANGLES, 0, models[VIDEOCAMERA].faces().size()*3);  
    
    // Terra
    glBindVertexArray (VAO_Terra);
    identTransform();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    // Paret
    ParetTransform();
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  }

  glBindVertexArray (0);
}

void MyGLWidget::iniCamera () 
{
  dist = 2*radiEscena;
  znear = dist - radiEscena;
  zfar = dist + radiEscena;
  raw = float(width())/height();
  fov = 2.0 * asin(radiEscena / dist);
  alfa = asin(radiEscena/dist);
  theta = float(M_PI/4.0);
  psi = 0.0;
  projectTransform();
  viewTransform();
}

void MyGLWidget::iniEscena()
{
  //Calcul tenint en compte altura 4 de paret (inclou altures dels altres objectes) i
  //i el tamany del terra
  radiEscena = distance(glm::vec3(-4.0, 0.0, -4.0), glm::vec3(4.0, 3.0, 4.0))/2.0;
  centreEscena = (glm::vec3(-4.0, 0.0, -4.0) + glm::vec3(4.0, 3.0, 4.0));
  centreEscena = centreEscena/glm::vec3(2.0);
}

void MyGLWidget::iniCamera2() {
    obs2 = glm::vec3(-4,3,-4);
    fov2 = glm::radians(float(60));
    znear2 = 0.25;
    zfar2 = 10;
    vrp2 = glm::vec3(-2,0,-2);
    up = glm::vec3(0,1,0);
    viewTransform2();
    projectTransform2();
}


MyGLWidget::~MyGLWidget()
{

}


void MyGLWidget::RickTransform() {
    glm::mat4 TG(1.0f); 
    TG = glm::translate(TG, glm::vec3(-2.0, 0.0, -2.0));
    TG = glm::rotate(TG, float(M_PI), glm::vec3(0.0, 1.0, 0.0));  
    TG = glm::scale(TG, glm::vec3(escalaModels[RICK]));
    TG = glm::translate(TG, -centreBaseModels[RICK]);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}
    
void MyGLWidget::MortyTransform() {
   glm::mat4 TG(1.0f);
   TG = glm::translate(TG, posMorty);
   TG = glm::rotate(TG, angleMorty, glm::vec3(0.0, 1.0, 0.0));
   TG = glm::scale(TG, glm::vec3(escalaModels[MORTY]));
   TG = glm::translate(TG, -centreBaseModels[MORTY]);
   glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::VideoCameraTransform() {
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, glm::vec3(-4.0, 3.0, -4.0));
    TG = glm::rotate(TG, rota_cam*float(M_PI/4.0), glm::vec3(0.0, 1.0, 0.0));
    TG = glm::rotate(TG, float(M_PI/4.0), glm::vec3(1.0, 0.0, 0.0));
    TG = glm::scale(TG, glm::vec3(escalaModels[VIDEOCAMERA]));
    TG = glm::translate(TG, -centreBaseModels[VIDEOCAMERA]);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::projectTransform () {
   //glm::perspective (FOV en radians, ra window, Znear, Zfar);
    glm::mat4 Proj = glm::perspective (fov, raw, znear, zfar);
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, &Proj[0][0]);
}
    
void MyGLWidget::viewTransform() {
    //LL2GLWidget::viewTransform();
    glm::mat4 View(1.0);
  	View = glm::translate(View, glm::vec3(0., 0., -dist));
    View = glm::rotate(View, theta, glm::vec3(1., 0., 0.));
    View = glm::rotate(View, -psi, glm::vec3(0., 1., 0.));
    View = glm::translate(View, -centreEscena);
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}

void MyGLWidget::projectTransform2() {
    glm::mat4 Proj(1.0f);
    Proj = glm::perspective (fov2, raw, znear2, zfar2);
    glUniformMatrix4fv (projLoc, 1, GL_FALSE, &Proj[0][0]); 
}

void MyGLWidget::viewTransform2() {
    glm::mat4 View(1.0f);
    View = glm::lookAt (obs2, vrp2, up);
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &View[0][0]);
}
    
 void MyGLWidget::mouseMoveEvent (QMouseEvent *e) {
    //LL2GLWidget::mouseMoveEvent(e);
    makeCurrent();
	
	if(e->x() > factorAngleX) psi -= 0.03;
	else if(e->x() < factorAngleX) psi += 0.03;
	
	if(e->y() > factorAngleY) theta -= 0.03;
	else if(e->y() < factorAngleY) theta += 0.03;
	
	factorAngleX = e->x();
	factorAngleY = e->y();
	viewTransform();
	update();
}

void MyGLWidget::keyPressEvent (QKeyEvent *event) {
  makeCurrent();
  switch (event->key()) {
    case Qt::Key_Up: { 
    	posMorty = posMorty + glm::vec3(sin(angleMorty), 0, cos(angleMorty))*glm::vec3(0.1);    	
        break;
    }
    case Qt::Key_Down: {
	    posMorty = posMorty -  glm::vec3(sin(angleMorty), 0, cos(angleMorty))*glm::vec3(0.1);
        break;
    }
    case Qt::Key_Left: {
        angleMorty += glm::radians(float(45));
        break;
    }
    case Qt::Key_Right: {
        angleMorty -= glm::radians(float(45));
        break;
    }
    case Qt::Key_Q: {
        if (rota_cam < M_PI/2) {
            rota_cam += glm::radians(float(1));
            float auxDist = glm::distance(glm::vec2(obs2.x, obs2.z), glm::vec2(vrp2.x, vrp2.z));
            vrp2 = obs2 + glm::vec3(auxDist*glm::sin(rota_cam),0, auxDist*glm::cos(rota_cam));
            vrp2.y = 0;
            viewTransform2();
        }
        break;
    }
    case Qt::Key_E: {
        if (rota_cam > 0) {
            rota_cam -= glm::radians(float(1));
            float auxDist = glm::distance(glm::vec2(obs2.x, obs2.z), glm::vec2(vrp2.x, vrp2.z));
            vrp2 = obs2 + glm::vec3(auxDist*glm::sin(rota_cam),0, auxDist*glm::cos(rota_cam));
            vrp2.y = 0;
            viewTransform2();
        }
        break;
    }
    case Qt::Key_C: {
        cam2 = not cam2;
        break;
    }
    case Qt::Key_R: {
        theta = float(M_PI/4.0);
        psi = 0.0;
        cam2 = false;
        rota_cam = 1.0f;
        angleMorty = 0.0f;
        posMorty = glm::vec3(1,0,0);
        colR = false;
        vrp2 = glm::vec3(-2,0,-2);
        break;
    }
    case Qt::Key_G: {
        colR = not colR;
        break;
    }

    default: event->ignore(); break;
  }
  update();
}

void MyGLWidget::carregaShaders() {
    LL2GLWidget::carregaShaders();
    verde  = glGetUniformLocation (program->programId(), "verd");
    verdR = glGetUniformLocation (program->programId(), "verdR");
}