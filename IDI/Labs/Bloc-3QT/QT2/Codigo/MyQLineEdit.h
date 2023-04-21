#include <QLineEdit>

class MyQLineEdit: public QLineEdit
{
    Q_OBJECT
    public:
    MyQLineEdit(QWidget *parent);

    public slots:
    void capturarReturn();
    signals:
    void enviarTexto(const QString &);

};