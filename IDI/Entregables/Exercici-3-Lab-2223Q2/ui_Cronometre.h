/********************************************************************************
** Form generated from reading UI file 'Cronometre.ui'
**
** Created by: Qt User Interface Compiler version 5.15.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CRONOMETRE_H
#define UI_CRONOMETRE_H

#include <MyQLCDNumber.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Cronometre
{
public:
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout_4;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_5;
    QLabel *label_6;
    QSpacerItem *horizontalSpacer_6;
    QHBoxLayout *horizontalLayout_3;
    QLCDNumber *lcdNumber;
    QLCDNumber *lcdNumber_2;
    QLCDNumber *lcdNumber_3;
    MyQLCDNumber *lcdNumber_4;
    QVBoxLayout *verticalLayout_2;
    QSpacerItem *verticalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_3;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *pushButton_4;

    void setupUi(QWidget *Cronometre)
    {
        if (Cronometre->objectName().isEmpty())
            Cronometre->setObjectName(QString::fromUtf8("Cronometre"));
        Cronometre->resize(840, 481);
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        Cronometre->setFont(font);
        Cronometre->setStyleSheet(QString::fromUtf8("background-color: rgb(61, 56, 70);"));
        horizontalLayout_6 = new QHBoxLayout(Cronometre);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_5 = new QLabel(Cronometre);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setMinimumSize(QSize(50, 50));
        label_5->setMaximumSize(QSize(100, 100));
        QFont font1;
        font1.setPointSize(15);
        font1.setBold(true);
        font1.setWeight(75);
        label_5->setFont(font1);
        label_5->setStyleSheet(QString::fromUtf8("\n"
"\n"
"color: rgb(255, 255, 255);"));

        horizontalLayout_4->addWidget(label_5);

        label_6 = new QLabel(Cronometre);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setMinimumSize(QSize(200, 50));
        label_6->setMaximumSize(QSize(200, 100));
        QFont font2;
        font2.setPointSize(18);
        font2.setBold(false);
        font2.setWeight(50);
        label_6->setFont(font2);
        label_6->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 100, 100);\n"
"color: rgb(255, 255, 255);"));
        label_6->setFrameShape(QFrame::Box);
        label_6->setFrameShadow(QFrame::Sunken);
        label_6->setLineWidth(4);

        horizontalLayout_4->addWidget(label_6);


        horizontalLayout_5->addLayout(horizontalLayout_4);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_6);


        verticalLayout_3->addLayout(horizontalLayout_5);


        verticalLayout_4->addLayout(verticalLayout_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        lcdNumber = new QLCDNumber(Cronometre);
        lcdNumber->setObjectName(QString::fromUtf8("lcdNumber"));
        lcdNumber->setMinimumSize(QSize(200, 100));
        QFont font3;
        font3.setPointSize(20);
        font3.setBold(false);
        font3.setWeight(50);
        lcdNumber->setFont(font3);
        lcdNumber->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 100, 100);"));
        lcdNumber->setLineWidth(3);
        lcdNumber->setDigitCount(6);

        horizontalLayout_3->addWidget(lcdNumber);

        lcdNumber_2 = new QLCDNumber(Cronometre);
        lcdNumber_2->setObjectName(QString::fromUtf8("lcdNumber_2"));
        lcdNumber_2->setMinimumSize(QSize(200, 100));
        lcdNumber_2->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 100, 100);"));
        lcdNumber_2->setFrameShape(QFrame::Box);
        lcdNumber_2->setLineWidth(3);
        lcdNumber_2->setDigitCount(6);

        horizontalLayout_3->addWidget(lcdNumber_2);

        lcdNumber_3 = new QLCDNumber(Cronometre);
        lcdNumber_3->setObjectName(QString::fromUtf8("lcdNumber_3"));
        lcdNumber_3->setMinimumSize(QSize(200, 100));
        QFont font4;
        font4.setPointSize(30);
        font4.setBold(false);
        font4.setWeight(50);
        lcdNumber_3->setFont(font4);
        lcdNumber_3->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 100, 100);"));
        lcdNumber_3->setLineWidth(3);
        lcdNumber_3->setDigitCount(6);

        horizontalLayout_3->addWidget(lcdNumber_3);

        lcdNumber_4 = new MyQLCDNumber(Cronometre);
        lcdNumber_4->setObjectName(QString::fromUtf8("lcdNumber_4"));
        lcdNumber_4->setMinimumSize(QSize(200, 100));
        lcdNumber_4->setStyleSheet(QString::fromUtf8("background-color: rgb(100, 100, 100);"));
        lcdNumber_4->setLineWidth(3);
        lcdNumber_4->setDigitCount(6);

        horizontalLayout_3->addWidget(lcdNumber_4);


        verticalLayout_4->addLayout(horizontalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButton = new QPushButton(Cronometre);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setMinimumSize(QSize(200, 50));
        pushButton->setFont(font);
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(143, 240, 164);"));
        pushButton->setCheckable(false);

        horizontalLayout->addWidget(pushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButton_3 = new QPushButton(Cronometre);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(200, 50));
        pushButton_3->setFont(font);
        pushButton_3->setStyleSheet(QString::fromUtf8("background-color: rgb(153, 193, 241);"));

        horizontalLayout->addWidget(pushButton_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout);


        verticalLayout_4->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_4);

        pushButton_4 = new QPushButton(Cronometre);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setMinimumSize(QSize(150, 50));
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(246, 0, 0);"));

        horizontalLayout_2->addWidget(pushButton_4);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_4->addLayout(verticalLayout);


        horizontalLayout_6->addLayout(verticalLayout_4);


        retranslateUi(Cronometre);
        QObject::connect(pushButton_4, SIGNAL(released()), Cronometre, SLOT(close()));
        QObject::connect(lcdNumber_4, SIGNAL(enviarsec(int)), lcdNumber_3, SLOT(display(int)));
        QObject::connect(lcdNumber_4, SIGNAL(enviarmin(int)), lcdNumber_2, SLOT(display(int)));
        QObject::connect(lcdNumber_4, SIGNAL(enviarhora(int)), lcdNumber, SLOT(display(int)));
        QObject::connect(lcdNumber_4, SIGNAL(enviarRec(QString)), label_6, SLOT(setText(QString)));
        QObject::connect(lcdNumber_4, SIGNAL(canviaColLCD(QString)), lcdNumber_3, SLOT(setStyleSheet(QString)));
        QObject::connect(lcdNumber_4, SIGNAL(canviaColLCD(QString)), lcdNumber_2, SLOT(setStyleSheet(QString)));
        QObject::connect(lcdNumber_4, SIGNAL(canviaColLCD(QString)), lcdNumber, SLOT(setStyleSheet(QString)));
        QObject::connect(lcdNumber_4, SIGNAL(canviaColLCD(QString)), lcdNumber_4, SLOT(setStyleSheet(QString)));
        QObject::connect(lcdNumber_4, SIGNAL(canviaColBot(QString)), pushButton, SLOT(setStyleSheet(QString)));
        QObject::connect(pushButton, SIGNAL(clicked()), lcdNumber_4, SLOT(tractaClick()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), lcdNumber_4, SLOT(tractaRestart()));

        QMetaObject::connectSlotsByName(Cronometre);
    } // setupUi

    void retranslateUi(QWidget *Cronometre)
    {
        Cronometre->setWindowTitle(QCoreApplication::translate("Cronometre", "Cronometre", nullptr));
        label_5->setText(QCoreApplication::translate("Cronometre", "R\303\251cord:", nullptr));
        label_6->setText(QString());
        pushButton->setText(QCoreApplication::translate("Cronometre", "Start/Stop", nullptr));
#if QT_CONFIG(shortcut)
        pushButton->setShortcut(QCoreApplication::translate("Cronometre", "Alt+S", nullptr));
#endif // QT_CONFIG(shortcut)
        pushButton_3->setText(QCoreApplication::translate("Cronometre", "Restart", nullptr));
#if QT_CONFIG(shortcut)
        pushButton_3->setShortcut(QCoreApplication::translate("Cronometre", "Alt+R", nullptr));
#endif // QT_CONFIG(shortcut)
        pushButton_4->setText(QCoreApplication::translate("Cronometre", "Quit", nullptr));
#if QT_CONFIG(shortcut)
        pushButton_4->setShortcut(QCoreApplication::translate("Cronometre", "Alt+Q", "Alt+q"));
#endif // QT_CONFIG(shortcut)
    } // retranslateUi

};

namespace Ui {
    class Cronometre: public Ui_Cronometre {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CRONOMETRE_H
