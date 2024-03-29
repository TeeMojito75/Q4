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

void MyGLWidget::ini_camera() {
   for (unsigned int i = 0; i < m.vertices().size(); i+=3) {
        if (m.vertices()[i] > emax.x or i == 0) emax.x = m.vertices()[i];
        if (m.vertices()[i] < emin.x or i == 0) emin.x = m.vertices()[i];
        if (m.vertices()[i+1] > emax.y or i == 0) emax.y = m.vertices()[i+1];
        if (m.vertices()[i+1] < emin.y or i == 0) emin.y = m.vertices()[i+1];
        if (m.vertices()[i+2] > emax.z or i == 0) emax.z = m.vertices()[i+2];
        if (m.vertices()[i+2] < emin.z or i == 0) emin.z = m.vertices()[i+2];
   }
    alt = emax.y - emin.y;
    escala = 4/alt;
    centro_P = glm::vec3((emax.x+emin.x)/2,(emax.y+emin.y)/2,(emax.z+emin.z)/2);
    if (2.5 > emax.x) emax.x = 2.5;
    if (2.5 > emax.z) emax.z = 2.5;
    if (-2.5 < emin.x) emin.x = -2.5;
    if (-2.5 > emin.z) emin.z = -2.5;
    if (0.0 < emin.y) emin.y = 0.0;


    centro = glm::vec3(0.0, 2.0,0.0);
    R = glm::distance(glm::vec3(2.5,0.0,2.5),glm::vec3(-2.5,0.0,-2.5))/2;
    d = 2*R;
    alfa_ini = glm::asin(R/d);
    VRP = centro; 
    OBS = centro+glm::vec3(0,0,d);
    up = glm::vec3(0,1,0);
    FOV = 2*alfa_ini;
    ra = float(width())/float(height());
    znear = d-R;
    zfar = d+R;
    viewTransform();
    projectTransform();
}

void MyGLWidget::carregaShaders() {
    BL2GLWidget::carregaShaders();
    projLoc = glGetUniformLocation (program->programId(), "proj");
    viewLoc = glGetUniformLocation (program->programId(), "view");
    TGLoc = glGetUniformLocation (program->programId(), "TG");
    colorLoc = glGetAttribLocation (program->programId(), "color");
}

void MyGLWidget::modelTransform() {
    //BL2GLWidget::modelTransform();
    glm::mat4 TG(1.0f);
    TG = rotate(TG, rotation,  glm::vec3(0.0, 0.1, 0.0));
    TG = glm::translate(TG, glm::vec3(0.0,2.0,0.0));
    TG = glm::scale(TG, glm::vec3(escala));
    TG = glm::translate(TG, -centro_P);
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}

/*
void MyGLWidget::modelTransformGR() {
    glm::mat4 TG(1.0f);
    TG = glm::translate(TG, escala*glm::vec3(0.0, -1.0, 0.0));
    
    glUniformMatrix4fv(transLoc, 1, GL_FALSE, &TG[0][0]);
}*/


void MyGLWidget::projectTransform () {
// glm::perspective (FOV en radians, ra window, znear, zfar)
    if (not ortho) {
        glm::mat4 proj = glm::perspective (FOV, ra, znear, zfar);
        glUniformMatrix4fv (projLoc, 1, GL_FALSE, &proj[0][0]); 
    }
    else {
        //glm::ortho (left, rigth, bottom, top, znear, zfar)
        glm::mat4 proj; 
        if (ra > 1)  proj = glm::ortho(-R*ra, R*ra, -R, R, znear, zfar);
        else proj = glm::ortho(-R, R, -R/ra, R/ra, znear, zfar);
        glUniformMatrix4fv (projLoc, 1, GL_FALSE, &proj[0][0]); 
    }
}

void MyGLWidget::viewTransform() {
    // glm::lookAt (OBS, VRP, UP)
    glm::mat4 view = glm::lookAt (OBS, VRP, up);
    glUniformMatrix4fv (viewLoc, 1, GL_FALSE, &view[0][0]);
}



void MyGLWidget::paintGL () 
{
    BL2GLWidget::paintGL();
// useu els paràmetres que considereu (els que hi ha són els de per defecte)
//  glViewport (0, 0, ample, alt);
  
  // Esborrem el frame-buffer
  glClear (GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
  projectTransform();
  viewTransform();
  // Carreguem la transformació de model
  modelTransform();
  
  // Activem el VAO per a pintar la caseta 
  glBindVertexArray (VAO_Homer);
  
  // pintem
  glDrawArrays(GL_TRIANGLES, 0, m.faces().size()*3);

  glBindVertexArray (VAO_Terra);
 
  BL2GLWidget::modelTransform();
  
  glDrawArrays(GL_TRIANGLES, 0, 6); 

  glBindVertexArray (0);

  
}

void MyGLWidget::creaBuffers() {
  m.load ("./Model/legoman-assegut.obj");
  glGenVertexArrays(1, &VAO_Homer);
  glBindVertexArray(VAO_Homer);

  GLuint VBO_Homer[2];
  glGenBuffers(2, VBO_Homer);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[0]);
  glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces().size() * 3 * 3, m.VBO_vertices(), GL_STATIC_DRAW);
  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_Homer[1]);
  glBufferData (GL_ARRAY_BUFFER, sizeof(GLfloat) * m.faces().size() * 3 * 3, m.VBO_matdiff(), GL_STATIC_DRAW);
  // Activem l'atribut colorLoc
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);

     glm::vec3 Vertices[6] = {
        glm::vec3(2.5,0.0,2.5),
        glm::vec3(-2.5,0.0,2.5),
        glm::vec3(-2.5,0.0,-2.5),
        glm::vec3(-2.5,0.0,-2.5),
        glm::vec3(2.5,0.0,-2.5),
        glm::vec3(2.5,0.0,2.5)
    };
    
    glm::vec3 color[6] = {
        glm::vec3(1,0,0),
        glm::vec3(0,1,0),
        glm::vec3(0,0,1),
        glm::vec3(0,0,1),
        glm::vec3(0,1,0),
        glm::vec3(1,0,0)
  };
      // Creació del Vertex Array Object (VAO) que usarem per pintar el quadrat                 
   glGenVertexArrays(1, &VAO_Terra);
   glBindVertexArray(VAO_Terra);

  GLuint VBO_Terra[2];
  glGenBuffers(2, VBO_Terra);
  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[0]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(Vertices), Vertices, GL_STATIC_DRAW);

  // Activem l'atribut vertexLoc
  glVertexAttribPointer(vertexLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(vertexLoc);

  glBindBuffer(GL_ARRAY_BUFFER, VBO_Terra[1]);
  glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

  // Activem l'atribut colorLoc
  glVertexAttribPointer(colorLoc, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(colorLoc);      

  glBindVertexArray (0);
}



void MyGLWidget::initializeGL() {
    BL2GLWidget::initializeGL();
    glEnable(GL_DEPTH_TEST);
    ini_camera();
}


void MyGLWidget::resizeGL (int width, int height) {
    
    ra = float(width)/float(height);

    if (ra < 1) {
        float alfaNou = atan(tan(alfa_ini) / ra);
        FOV = 2*alfaNou;
    }
    else {
        FOV = 2*alfa_ini;
    }
   
}

void MyGLWidget::keyPressEvent (QKeyEvent *event) {
   
    makeCurrent();
    switch (event->key()) {
    case Qt::Key_S: { // escalar a més gran
        escala += 0.05;
        break;
    }
    case Qt::Key_D: { // escalar a més petit
        escala -= 0.05;
        break;
    }
    case Qt::Key_R: { //rotar 45 graus
        rotation += float(M_PI)/4;
        break;
    }
    case Qt::Key_E: { //rotar 45 graus
        rotation -= float(M_PI)/4;
        break;
    }
     case Qt::Key_O: { //rcamera ortogonal
        ortho = not ortho;
        break;
    }
    default: event->ignore(); break;
  }
  update();
}

MyGLWidget::~MyGLWidget() {
}


