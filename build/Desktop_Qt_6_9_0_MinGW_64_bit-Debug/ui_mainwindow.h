/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *Password_txt;
    QLineEdit *passwordEdit;
    QLabel *label;
    QLineEdit *decryptPasswordEdit;
    QSplitter *splitter;
    QPushButton *pushButton_2;
    QPushButton *Decrypt_button;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *Explprer_button;
    QLabel *Name_txt;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(578, 153);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        Password_txt = new QLabel(centralwidget);
        Password_txt->setObjectName("Password_txt");

        horizontalLayout->addWidget(Password_txt);

        passwordEdit = new QLineEdit(centralwidget);
        passwordEdit->setObjectName("passwordEdit");

        horizontalLayout->addWidget(passwordEdit);

        label = new QLabel(centralwidget);
        label->setObjectName("label");

        horizontalLayout->addWidget(label);

        decryptPasswordEdit = new QLineEdit(centralwidget);
        decryptPasswordEdit->setObjectName("decryptPasswordEdit");

        horizontalLayout->addWidget(decryptPasswordEdit);


        gridLayout->addLayout(horizontalLayout, 3, 0, 1, 1);

        splitter = new QSplitter(centralwidget);
        splitter->setObjectName("splitter");
        splitter->setOrientation(Qt::Orientation::Horizontal);
        pushButton_2 = new QPushButton(splitter);
        pushButton_2->setObjectName("pushButton_2");
        splitter->addWidget(pushButton_2);
        Decrypt_button = new QPushButton(splitter);
        Decrypt_button->setObjectName("Decrypt_button");
        splitter->addWidget(Decrypt_button);

        gridLayout->addWidget(splitter, 4, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        Explprer_button = new QPushButton(centralwidget);
        Explprer_button->setObjectName("Explprer_button");

        horizontalLayout_2->addWidget(Explprer_button);


        gridLayout->addLayout(horizontalLayout_2, 2, 0, 1, 1);

        Name_txt = new QLabel(centralwidget);
        Name_txt->setObjectName("Name_txt");
        Name_txt->setMouseTracking(true);
        Name_txt->setLayoutDirection(Qt::LayoutDirection::LeftToRight);
        Name_txt->setFrameShadow(QFrame::Shadow::Plain);
        Name_txt->setTextFormat(Qt::TextFormat::AutoText);

        gridLayout->addWidget(Name_txt, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        Password_txt->setText(QCoreApplication::translate("MainWindow", "Encryption password:", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Decryption password:", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "Encrypt", nullptr));
        Decrypt_button->setText(QCoreApplication::translate("MainWindow", "Decrypt", nullptr));
        Explprer_button->setText(QCoreApplication::translate("MainWindow", "Explorer", nullptr));
        Name_txt->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:11pt; font-weight:700; font-style:italic;\"> Encryption/Decryption</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
