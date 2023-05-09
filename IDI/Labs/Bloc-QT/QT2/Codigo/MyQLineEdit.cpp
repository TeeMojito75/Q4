#include "MyQLineEdit.h"

MyQLineEdit::MyQLineEdit(QWidget *parent): QLineEdit(parent)
{

}

void MyQLineEdit::capturarReturn()
{
    emit enviarTexto(text());
}