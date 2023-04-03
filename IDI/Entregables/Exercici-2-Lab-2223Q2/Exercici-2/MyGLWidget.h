#include "LL2GLWidget.h"

#include "model.h"

class MyGLWidget : public LL2GLWidget {
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : LL2GLWidget(parent) {}
    ~MyGLWidget();

    virtual void initializeGL();
    virtual void RickTransform();
    virtual void MortyTransform();
    virtual void VideoCameraTransform();
    virtual void viewTransform();
    virtual void projectTransform();
    virtual void iniCamera();  
    virtual void iniEscena();
    
    virtual void mouseMoveEvent (QMouseEvent *event);
    virtual void keyPressEvent (QKeyEvent *event);

    
    //vars camera euler
    float psi, theta, raw, dist;
    
    float rota_cam;
  protected:

  private:

  
    int printOglError(const char file[], int line, const char func[]);
    
};
