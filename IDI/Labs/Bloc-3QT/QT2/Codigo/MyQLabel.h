#include <QLabel>

class MyQLabel: public QLabel {
    Q_OBJECT

    public:
    MyQLabel(QWidget *parent);
    
    int contadorc = 0;
    bool abierto = false;
    public slots:
    void incrementarContador();
    void incrementarContadorC();
    void cambiarColor();

};