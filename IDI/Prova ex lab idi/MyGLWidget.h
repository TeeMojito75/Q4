#include "ExamGLWidget.h"

class MyGLWidget:public ExamGLWidget
{
  Q_OBJECT

  public:
    MyGLWidget(QWidget *parent=0) : ExamGLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void paintGL ();
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void modelTransformCub (float escala, float angle);
    virtual void modelTransformPatricio ();
    virtual void projectTransform ();
    virtual void viewTransform ();

    virtual void initializeGL ();
    virtual void resizeGL (int width, int height);
   

  private:
    int printOglError(const char file[], int line, const char func[]);

    int iteraPat = 0;
    int iteraCapses = 0;
    bool borraPat = true;

    bool groc = true;

    public slots:
    void Capsa1();
    void Capsa2();
    void Capsa3();
    void Pers();
    void Orto();

    signals:
    void iniButton();
    void modCam();
    void modCam1();
    void modCapsa0();
    void modCapsa1();
    void modCapsa2();
    void modReset();
};
