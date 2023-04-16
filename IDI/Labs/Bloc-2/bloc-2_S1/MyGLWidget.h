// MyGLWidget.h
#include "BL2GLWidget.h"
#include "model.h"

class MyGLWidget : public BL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : BL2GLWidget(parent) {}
    ~MyGLWidget();

    virtual void carregaShaders ();
    virtual void modelTransform();
    void projectTransform();
    void viewTransform();
    void ini_camera();
    virtual void paintGL ();
    virtual void creaBuffers();
    void creaBuffersTerra();
    virtual void initializeGL();
    virtual void keyPressEvent (QKeyEvent *event);


    GLuint projLoc;
    GLuint viewLoc;
    GLuint TGLoc;
    GLuint colorLoc;
    GLuint VAO_Homer;
    GLuint VAO_Terra;

    //vars ini_camera
    glm::vec3 OBS;
    glm::vec3 VRP;
    glm::vec3 up;
    float FOV;
    float ra;
    float znear;
    float zfar;

    float rotation = 0.0f;
    float escala = 1.0f;

    Model m;
    
  private:
    int printOglError(const char file[], int line, const char func[]);
};
