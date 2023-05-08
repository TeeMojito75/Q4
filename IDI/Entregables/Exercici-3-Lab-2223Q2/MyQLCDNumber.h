#include <QLCDNumber>
#include <QTimer>
#include <QTime>

class MyQLCDNumber: public QLCDNumber
{
    Q_OBJECT
    public:
    MyQLCDNumber(QWidget *parent);
    bool start = true;

    public slots:
    void tractaClick();
    void tractaTimeout();
    void tractaRestart();

    signals:
    void enviarRec(QString record);
    void canviaColBot(QString col);
    void canviaColLCD(QString col);

    private:
    QTimer qtimer;
    QTime actu = QTime(0,0,0), record = QTime(0,0,0);
    
};