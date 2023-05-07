// MyForm.h – Ui::MyForm com a membre
#include "ui_Cronometre.h"
class Cronometre : public QWidget {
	Q_OBJECT
	
	public:
	Cronometre(QWidget *parent = 0);
	private:
	Ui::Cronometre ui;
};