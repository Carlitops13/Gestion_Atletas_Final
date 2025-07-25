/********************************************************************************
** Form generated from reading UI file 'logindialog.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINDIALOG_H
#define UI_LOGINDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_LoginDialog
{
public:
    QLabel *label;
    QLabel *label_2;
    QLineEdit *lineEdit_usuario;
    QLineEdit *lineEdit_password;
    QPushButton *pushButton_ingresar;

    void setupUi(QDialog *LoginDialog)
    {
        if (LoginDialog->objectName().isEmpty())
            LoginDialog->setObjectName("LoginDialog");
        LoginDialog->resize(359, 239);
        label = new QLabel(LoginDialog);
        label->setObjectName("label");
        label->setGeometry(QRect(90, 80, 61, 21));
        label_2 = new QLabel(LoginDialog);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(80, 130, 81, 21));
        lineEdit_usuario = new QLineEdit(LoginDialog);
        lineEdit_usuario->setObjectName("lineEdit_usuario");
        lineEdit_usuario->setGeometry(QRect(150, 80, 113, 24));
        lineEdit_password = new QLineEdit(LoginDialog);
        lineEdit_password->setObjectName("lineEdit_password");
        lineEdit_password->setGeometry(QRect(150, 130, 113, 24));
        pushButton_ingresar = new QPushButton(LoginDialog);
        pushButton_ingresar->setObjectName("pushButton_ingresar");
        pushButton_ingresar->setGeometry(QRect(170, 190, 80, 24));

        retranslateUi(LoginDialog);

        QMetaObject::connectSlotsByName(LoginDialog);
    } // setupUi

    void retranslateUi(QDialog *LoginDialog)
    {
        LoginDialog->setWindowTitle(QCoreApplication::translate("LoginDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("LoginDialog", "Usuario:", nullptr));
        label_2->setText(QCoreApplication::translate("LoginDialog", "Contrase\303\261a:", nullptr));
        pushButton_ingresar->setText(QCoreApplication::translate("LoginDialog", "Ingresar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginDialog: public Ui_LoginDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINDIALOG_H
