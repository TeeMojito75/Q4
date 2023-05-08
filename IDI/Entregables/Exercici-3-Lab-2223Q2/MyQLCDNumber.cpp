#include "MyQLCDNumber.h"

MyQLCDNumber::MyQLCDNumber(QWidget *parent): QLCDNumber(parent)
{
    connect(&qtimer, SIGNAL(timeout()), this, SLOT(tractaTimeout()));
    setDigitCount(12);
    display(actu.toString("hh:mm:ss.zzz"));
}

void MyQLCDNumber::tractaClick() 
{
    if (start) 
    {
        qtimer.start(1);
        emit canviaColBot("background-color: rgb(246, 0, 0);");
    }
    else 
    {
        if (actu != QTime(0,0,0)) record = actu;
        qtimer.stop();
        emit canviaColBot("background-color: rgb(143, 240, 164);");
        emit enviarRec(record.toString("hh:mm:ss.zzz"));
    }
    start = not start;
}

void MyQLCDNumber::tractaTimeout() 
{
    actu = actu.addMSecs(1);
    display(actu.toString("hh:mm:ss.zzz"));
    
    if (record != QTime(0,0,0))
    {
        if (actu < record) emit canviaColLCD("background-color: rgb(143, 240, 164);");
        else if (actu == record) emit canviaColLCD("background-color: rgb(100, 100, 100);");
        else emit canviaColLCD("background-color: rgb(246, 0, 0);");
    } 
}

void MyQLCDNumber::tractaRestart()
{
    qtimer.stop();
    if (not start)
    { 
        start = not start;
        emit canviaColBot("background-color: rgb(143, 240, 164);");
    }
    actu = QTime(0,0,0);
    emit canviaColLCD("background-color: rgb(100, 100, 100);");
    display(actu.toString("hh:mm:ss.zzz"));
}