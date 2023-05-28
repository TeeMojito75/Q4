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


void MyGLWidget::initializeGL ()
{
  LL4GLWidget::initializeGL();
  MycarregaShaders();
  rotaBall = 0.0;
  rotaFM = 0.0; 

  posFocusEscena = glm::vec3(5.0f,10.0f,5.0f);
  glUniform3fv(focusEscenaLoc, 1, &posFocusEscena[0]); 
  colEscena = glm::vec3(0.4, 0.4, 0.4);
  glUniform3fv(colEscenaLoc, 1, &colEscena[0]);

  posFocusR = glm::vec3(1.2f, 0.0f, 0.0f);
  glUniform3fv(PRL, 1, &posFocusR[0]);
  colR = glm::vec3(0.4f,0.0f,0.0f);
  glUniform3fv(CRL, 1, &colR[0]); 

  posFocusG = glm::vec3(-1.2f, 0.0f, 0.0f);
  glUniform3fv(PGL, 1, &posFocusG[0]);
  colG = glm::vec3(0.0f,0.4f,0.0f);
  glUniform3fv(CGL, 1, &colG[0]); 

  posFocusB = glm::vec3(0.0f, 0.0f, 1.2f);
  glUniform3fv(PBL, 1, &posFocusB[0]);
  colB = glm::vec3(0.0f,0.0f,0.4f);
  glUniform3fv(CBL, 1, &colB[0]); 

  posFocusY = glm::vec3(0.0f, 0.0f, -1.2f);
  glUniform3fv(PYL, 1, &posFocusY[0]);
  colY = glm::vec3(0.4f,0.4f,0.0f);
  glUniform3fv(CYL, 1, &colY[0]); 

  escena = true;
}

void MyGLWidget::iniMaterialTerra ()
{
  // Donem valors al material del terra
  amb = glm::vec3(0.1,0.1,0.1);
  diff = glm::vec3(0.4,0.4,0.4);
  spec = glm::vec3(0.8,0.8,0.8);
  shin = 100;
}

void MyGLWidget::paintGL()
{
 // En cas de voler canviar els paràmetres del viewport, descomenteu la crida següent i
  // useu els paràmetres que considereu (els que hi ha són els de per defecte)
  // glViewport (0, 0, ample, alt);
  
  // Esborrem el frame-buffer i el depth-buffer
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  //Primero lucecita porque sinó las funciones siguientes pueden sobreescribir
  glm::vec3 aux = glm::vec3(View * glm::vec4(posFocusEscena, 1.0f));
  glUniform3fv(focusEscenaLoc, 1, &aux[0]); 

  // TERRA
  glBindVertexArray (VAO_Terra);
  modelTransformTerra ();
  glDrawArrays(GL_TRIANGLES, 0, 30);
  
  // MORTY
  glBindVertexArray (VAO_Morty);
  modelTransformMorty ();
  glDrawArrays(GL_TRIANGLES, 0, morty.faces().size()*3);
  
  // FANTASMA1
  glBindVertexArray (VAO_Fantasma);
  modelTransformFantasma (1.0f);
  glDrawArrays(GL_TRIANGLES, 0, fantasma.faces().size()*3);

  //FANTASMA2
  glBindVertexArray (VAO_Fantasma);
  modelTransformFantasma (9.0f);
  glDrawArrays(GL_TRIANGLES, 0, fantasma.faces().size()*3);

  // DISCO BALL
  glBindVertexArray (VAO_DiscoBall);
  modelTransformDiscoBall ();
  glDrawArrays(GL_TRIANGLES, 0, discoBall.faces().size()*3);

  
  glBindVertexArray(0);
}
  

void MyGLWidget::modelTransformMorty() 
{ 
  TG = glm::translate(glm::mat4(1.f), glm::vec3(5,0,5));
  TG = glm::rotate(TG, rotaFM, glm::vec3(0,1,0));
  TG = glm::scale(TG, glm::vec3(escalaMorty, escalaMorty, escalaMorty));
  TG = glm::translate(TG, -centreBaseMorty);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformDiscoBall() 
{ 
  TGdisco = glm::translate(glm::mat4(1.f), glm::vec3(5,5,5));
  TGdisco = glm::rotate(TGdisco, rotaBall, glm::vec3(0,1,0));
  TGdisco = glm::scale(TGdisco, glm::vec3(escalaDiscoBall, escalaDiscoBall, escalaDiscoBall));
  TGdisco = glm::translate(TGdisco, -centreBaseDiscoBall);

  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TGdisco[0][0]);

  glm::vec3 aux = glm::vec3(View * TGdisco * glm::vec4(posFocusR, 1.0f));
  glUniform3fv(PRL, 1, &aux[0]); 

  aux = glm::vec3(View * TGdisco * glm::vec4(posFocusG, 1.0f));
  glUniform3fv(PGL, 1, &aux[0]); 

  aux = glm::vec3(View * TGdisco * glm::vec4(posFocusB, 1.0f));
  glUniform3fv(PBL, 1, &aux[0]); 

  aux = glm::vec3(View * TGdisco * glm::vec4(posFocusY, 1.0f));
  glUniform3fv(PYL, 1, &aux[0]); 
}


void MyGLWidget::modelTransformFantasma (float posX)
{
  TG = glm::translate(glm::mat4(1.0f), glm::vec3(posX,0.5,5));
  TG = glm::rotate(TG, rotaFM, glm::vec3(0,1,0));
  TG = glm::scale(TG, glm::vec3(escalaFantasma, escalaFantasma, escalaFantasma));
  TG = glm::translate(TG, -centreBaseFantasma);
  
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::modelTransformTerra()
{
  glm::mat4 TG = glm::mat4(1.f);  // Matriu de transformació
  glUniformMatrix4fv (transLoc, 1, GL_FALSE, &TG[0][0]);
}

void MyGLWidget::mouseMoveEvent(QMouseEvent *e)
{
  makeCurrent();
  // Aqui cal que es calculi i s'apliqui la rotacio o el zoom com s'escaigui...
  if (DoingInteractive == ROTATE)
  {
    // Fem la rotació
    angleY += (e->x() - xClick) * M_PI / ample;
    viewTransform ();
  }

  xClick = e->x();
  yClick = e->y();

  update ();
}

void MyGLWidget::keyPressEvent(QKeyEvent* event) {
  makeCurrent();
  switch (event->key()) {
  case Qt::Key_A: {
      rotaFM += glm::radians(45.0f);
    break;
	}
  case Qt::Key_D: {
      rotaFM -= glm::radians(45.0f);
    break;
	}
  case Qt::Key_E: {
      if (escena) colEscena = glm::vec3(0,0,0);
      else colEscena = glm::vec3(0.4,0.4,0.4);
      escena = !escena;
   break;
	}
  case Qt::Key_B: {
      // ...
    break;
	}	
  case Qt::Key_R: {
      rotaBall += glm::radians(5.0f);
    break;
	}
  case Qt::Key_S: {
      // ...
    break;
	}	
  default: LL4GLWidget::keyPressEvent(event); break;
  }
  glUniform3fv(colEscenaLoc, 1, &colEscena[0]);
  update();
}

void MyGLWidget::MycarregaShaders()
{
  focusEscenaLoc = glGetUniformLocation (program->programId(), "posEscena");
  colEscenaLoc = glGetUniformLocation (program->programId(), "colEscena");

  PRL = glGetUniformLocation (program->programId(), "posR");
  CRL = glGetUniformLocation (program->programId(), "colR");

  PGL = glGetUniformLocation (program->programId(), "posG");
  CGL = glGetUniformLocation (program->programId(), "colG");

  PBL = glGetUniformLocation (program->programId(), "posB");
  CBL = glGetUniformLocation (program->programId(), "colB");

  PYL = glGetUniformLocation (program->programId(), "posY");
  CYL = glGetUniformLocation (program->programId(), "colY");

  TGDLoc = glGetUniformLocation (program->programId(), "TGdisco");
  
}
