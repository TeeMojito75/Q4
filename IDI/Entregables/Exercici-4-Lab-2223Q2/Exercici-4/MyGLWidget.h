// MyGLWidget.h
#include "LL4GLWidget.h"
#include <QTimer>

class MyGLWidget : public LL4GLWidget {
  Q_OBJECT
  public:
    MyGLWidget(QWidget *parent=0) : LL4GLWidget(parent) {}
    ~MyGLWidget();

  protected:
    virtual void mouseMoveEvent(QMouseEvent *e);
    virtual void keyPressEvent(QKeyEvent* event);

     // initializeGL - Aqui incluim les inicialitzacions del contexte grafic.
    virtual void initializeGL ();
    // paintGL - Mètode cridat cada cop que cal refrescar la finestra.
    // Tot el que es dibuixa es dibuixa aqui.
    virtual void paintGL ();
 
    virtual void iniMaterialTerra ();
    virtual void modelTransformTerra ();
    virtual void modelTransformMorty ();
    virtual void modelTransformFantasma (float posX);
    virtual void modelTransformDiscoBall ();
  
    void MycarregaShaders();
  private:
    int printOglError(const char file[], int line, const char func[]);

  //Pos focus llum
  GLuint focusEscenaLoc, PRL, PGL, PBL, PYL; 
  GLuint colEscenaLoc, CRL, CGL, CBL, CYL;
  GLuint TGDLoc;

  //Matriu pos focus llums
  glm::vec3 posFocusEscena, posFocusR, posFocusG, posFocusB, posFocusY;
  glm::vec3 colEscena, colR, colG, colB, colY; 

  glm::mat4 TG, TGdisco;

  //Rotacions
  float rotaBall;
  float rotaFM;

  bool escena;
  bool apagar;
  int iterador;

  //coses timer
  bool start;
  QTimer qtimer;

  public slots:
  void tractaTimeout(); 

};
