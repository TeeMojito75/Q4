/********************************************************************************
** Form generated from reading UI file 'MyForm.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MYFORM_H
#define UI_MYFORM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "MyQLabel.h"

QT_BEGIN_NAMESPACE

class Ui_MyForm
{
public:
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_6;
    MyQLabel *label;
    QRadioButton *radioButton;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    MyQLabel *label_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton_2;
    MyQLabel *label_4;
    QHBoxLayout *horizontalLayout_3;
    QPushButton *pushButton_3;
    MyQLabel *label_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_6;
    MyQLabel *label_7;

    void setupUi(QWidget *MyForm)
    {
        if (MyForm->objectName().isEmpty())
            MyForm->setObjectName(QString::fromUtf8("MyForm"));
        MyForm->resize(647, 520);
        verticalLayout_3 = new QVBoxLayout(MyForm);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label = new MyQLabel(MyForm);
        label->setObjectName(QString::fromUtf8("label"));
        label->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));

        horizontalLayout_6->addWidget(label);

        radioButton = new QRadioButton(MyForm);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));

        horizontalLayout_6->addWidget(radioButton);


        verticalLayout_2->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label_2 = new QLabel(MyForm);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout->addWidget(label_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        pushButton = new QPushButton(MyForm);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setEnabled(false);

        horizontalLayout->addWidget(pushButton);

        label_3 = new MyQLabel(MyForm);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        pushButton_2 = new QPushButton(MyForm);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setEnabled(false);

        horizontalLayout_2->addWidget(pushButton_2);

        label_4 = new MyQLabel(MyForm);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_2->addWidget(label_4);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        pushButton_3 = new QPushButton(MyForm);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setEnabled(false);

        horizontalLayout_3->addWidget(pushButton_3);

        label_5 = new MyQLabel(MyForm);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_3->addWidget(label_5);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_5->addLayout(verticalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_6 = new QLabel(MyForm);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_4->addWidget(label_6);

        label_7 = new MyQLabel(MyForm);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_4->addWidget(label_7);


        horizontalLayout_5->addLayout(horizontalLayout_4);


        verticalLayout_2->addLayout(horizontalLayout_5);


        verticalLayout_3->addLayout(verticalLayout_2);


        retranslateUi(MyForm);
        QObject::connect(radioButton, SIGNAL(released()), label, SLOT(cambiarColor()));
        QObject::connect(pushButton_2, SIGNAL(released()), label_7, SLOT(incrementarContador()));
        QObject::connect(radioButton, SIGNAL(toggled(bool)), pushButton_3, SLOT(setEnabled(bool)));
        QObject::connect(radioButton, SIGNAL(toggled(bool)), pushButton, SLOT(setEnabled(bool)));
        QObject::connect(pushButton_3, SIGNAL(released()), label_7, SLOT(incrementarContadorC()));
        QObject::connect(pushButton_3, SIGNAL(released()), label_5, SLOT(incrementarContador()));
        QObject::connect(radioButton, SIGNAL(toggled(bool)), pushButton_2, SLOT(setEnabled(bool)));
        QObject::connect(pushButton, SIGNAL(released()), label_7, SLOT(incrementarContador()));
        QObject::connect(pushButton, SIGNAL(released()), label_3, SLOT(incrementarContador()));
        QObject::connect(pushButton_2, SIGNAL(released()), label_4, SLOT(incrementarContador()));

        pushButton->setDefault(false);


        QMetaObject::connectSlotsByName(MyForm);
    } // setupUi

    void retranslateUi(QWidget *MyForm)
    {
        MyForm->setWindowTitle(QCoreApplication::translate("MyForm", "Form", nullptr));
        label->setText(QCoreApplication::translate("MyForm", "Cerrado", nullptr));
        radioButton->setText(QCoreApplication::translate("MyForm", "Obrir/Tancar Pas", nullptr));
        label_2->setText(QCoreApplication::translate("MyForm", "Total per vehicle:", nullptr));
        pushButton->setText(QCoreApplication::translate("MyForm", "Cotxes", nullptr));
        label_3->setText(QCoreApplication::translate("MyForm", "0", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MyForm", "Motos", nullptr));
        label_4->setText(QCoreApplication::translate("MyForm", "0", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MyForm", "Camions", nullptr));
        label_5->setText(QCoreApplication::translate("MyForm", "0", nullptr));
        label_6->setText(QCoreApplication::translate("MyForm", "Recaptaci\303\263 total:", nullptr));
        label_7->setText(QCoreApplication::translate("MyForm", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MyForm: public Ui_MyForm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MYFORM_H
