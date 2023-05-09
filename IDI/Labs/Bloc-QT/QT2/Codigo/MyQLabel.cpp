#include "MyQLabel.h"

MyQLabel::MyQLabel(QWidget *parent): QLabel(parent) {

}

void MyQLabel::incrementarContador() {
    contadorc++;
    setText(QString::number(contadorc));
}

void MyQLabel::incrementarContadorC() {
    contadorc += 4;
    setText(QString::number(contadorc));
}

void MyQLabel::cambiarColor()
{
    abierto = not abierto;
    if (abierto) {
        setStyleSheet("background-color: green;");
        setText("Abierto");
    }
    else {

        setStyleSheet("background-color: red;");
        setText("Cerrado");
    }
}