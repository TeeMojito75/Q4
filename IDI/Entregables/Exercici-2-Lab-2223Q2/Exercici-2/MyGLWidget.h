#include "LL2GLWidget.h"

#include "model.h"

class MyGLWidget : public LL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : LL2GLWidget(parent) {}
    ~MyGLWidget();

    virtual void initializeGL();
    virtual void resizeGL(int width, int height);
    virtual void paintGL();
    virtual void RickTransform();
    virtual void MortyTransform();
    virtual void VideoCameraTransform();
    virtual void viewTransform();
    virtual void projectTransform();
    virtual void iniCamera();  
    virtual void iniEscena();
    virtual void iniCamera2();
    virtual void viewTransform2();
    virtual void projectTransform2();
    virtual void carregaShaders();

    virtual void mouseMoveEvent (QMouseEvent *event);
    virtual void keyPressEvent (QKeyEvent *event);

    GLuint verde;
    GLuint verdR;
    //vars camera euler
    float psi, theta, raw, dist, alfa;
    
    float rota_cam;

    bool cam2;
    bool colR;

    float fov2, znear2, zfar2;
    glm::vec3 obs2, vrp2;
  protected:

  private:

  
    int printOglError(const char file[], int line, const char func[]);
    
};
