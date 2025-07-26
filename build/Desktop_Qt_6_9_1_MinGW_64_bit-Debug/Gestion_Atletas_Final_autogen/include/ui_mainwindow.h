/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.9.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget_atletas;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_id;
    QLabel *label_2;
    QLineEdit *lineEdit_nombre;
    QLabel *label_3;
    QSpinBox *spinBox_edad;
    QComboBox *comboBox_deporte;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton_registrar;
    QPushButton *pushButton_actualizar;
    QPushButton *pushButton_eliminar;
    QPushButton *pushButton_limpiar;
    QPushButton *pushButton_borrarTodo;
    QPushButton *pushButton_guardar;
    QLabel *label_4;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(919, 394);
        QFont font;
        font.setFamilies({QString::fromUtf8("Consolas")});
        MainWindow->setFont(font);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName("verticalLayout");
        tableWidget_atletas = new QTableWidget(centralwidget);
        tableWidget_atletas->setObjectName("tableWidget_atletas");

        verticalLayout->addWidget(tableWidget_atletas);


        gridLayout->addLayout(verticalLayout, 1, 0, 1, 1);

        formLayout = new QFormLayout();
        formLayout->setObjectName("formLayout");
        label = new QLabel(centralwidget);
        label->setObjectName("label");

        formLayout->setWidget(0, QFormLayout::ItemRole::LabelRole, label);

        label_id = new QLabel(centralwidget);
        label_id->setObjectName("label_id");

        formLayout->setWidget(0, QFormLayout::ItemRole::FieldRole, label_id);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        formLayout->setWidget(1, QFormLayout::ItemRole::LabelRole, label_2);

        lineEdit_nombre = new QLineEdit(centralwidget);
        lineEdit_nombre->setObjectName("lineEdit_nombre");

        formLayout->setWidget(1, QFormLayout::ItemRole::FieldRole, lineEdit_nombre);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        formLayout->setWidget(2, QFormLayout::ItemRole::LabelRole, label_3);

        spinBox_edad = new QSpinBox(centralwidget);
        spinBox_edad->setObjectName("spinBox_edad");
        spinBox_edad->setMinimum(18);
        spinBox_edad->setMaximum(65);

        formLayout->setWidget(2, QFormLayout::ItemRole::FieldRole, spinBox_edad);

        comboBox_deporte = new QComboBox(centralwidget);
        comboBox_deporte->addItem(QString());
        comboBox_deporte->addItem(QString());
        comboBox_deporte->addItem(QString());
        comboBox_deporte->addItem(QString());
        comboBox_deporte->addItem(QString());
        comboBox_deporte->addItem(QString());
        comboBox_deporte->addItem(QString());
        comboBox_deporte->addItem(QString());
        comboBox_deporte->setObjectName("comboBox_deporte");

        formLayout->setWidget(3, QFormLayout::ItemRole::FieldRole, comboBox_deporte);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        pushButton_registrar = new QPushButton(centralwidget);
        pushButton_registrar->setObjectName("pushButton_registrar");

        horizontalLayout->addWidget(pushButton_registrar);

        pushButton_actualizar = new QPushButton(centralwidget);
        pushButton_actualizar->setObjectName("pushButton_actualizar");

        horizontalLayout->addWidget(pushButton_actualizar);

        pushButton_eliminar = new QPushButton(centralwidget);
        pushButton_eliminar->setObjectName("pushButton_eliminar");

        horizontalLayout->addWidget(pushButton_eliminar);

        pushButton_limpiar = new QPushButton(centralwidget);
        pushButton_limpiar->setObjectName("pushButton_limpiar");

        horizontalLayout->addWidget(pushButton_limpiar);

        pushButton_borrarTodo = new QPushButton(centralwidget);
        pushButton_borrarTodo->setObjectName("pushButton_borrarTodo");

        horizontalLayout->addWidget(pushButton_borrarTodo);

        pushButton_guardar = new QPushButton(centralwidget);
        pushButton_guardar->setObjectName("pushButton_guardar");

        horizontalLayout->addWidget(pushButton_guardar);


        formLayout->setLayout(4, QFormLayout::ItemRole::FieldRole, horizontalLayout);

        label_4 = new QLabel(centralwidget);
        label_4->setObjectName("label_4");

        formLayout->setWidget(3, QFormLayout::ItemRole::LabelRole, label_4);


        gridLayout->addLayout(formLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 919, 19));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Gest\303\263n de Atletas", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "\360\237\252\252 ID: ", nullptr));
        label_id->setText(QString());
        label_2->setText(QCoreApplication::translate("MainWindow", "\360\237\217\203Nombre Completo del atleta: ", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\360\237\224\236 Edad: ", nullptr));
        comboBox_deporte->setItemText(0, QString());
        comboBox_deporte->setItemText(1, QCoreApplication::translate("MainWindow", "F\303\272tbol", nullptr));
        comboBox_deporte->setItemText(2, QCoreApplication::translate("MainWindow", "Calistenia", nullptr));
        comboBox_deporte->setItemText(3, QCoreApplication::translate("MainWindow", "Tennis", nullptr));
        comboBox_deporte->setItemText(4, QCoreApplication::translate("MainWindow", "Ecuavolley", nullptr));
        comboBox_deporte->setItemText(5, QCoreApplication::translate("MainWindow", "Gimnasia", nullptr));
        comboBox_deporte->setItemText(6, QCoreApplication::translate("MainWindow", "F\303\272tbol Sala", nullptr));
        comboBox_deporte->setItemText(7, QCoreApplication::translate("MainWindow", "Atletismo", nullptr));

        pushButton_registrar->setText(QCoreApplication::translate("MainWindow", "\360\237\223\235 Registrar", nullptr));
        pushButton_actualizar->setText(QCoreApplication::translate("MainWindow", "\360\237\224\204 Actualizar", nullptr));
        pushButton_eliminar->setText(QCoreApplication::translate("MainWindow", "\360\237\227\221\357\270\217 Eliminar", nullptr));
        pushButton_limpiar->setText(QCoreApplication::translate("MainWindow", "\360\237\247\271 Limpiar Campos", nullptr));
        pushButton_borrarTodo->setText(QCoreApplication::translate("MainWindow", "\360\237\206\221 Limpiar Tabla", nullptr));
        pushButton_guardar->setText(QCoreApplication::translate("MainWindow", "\360\237\222\276 Guardar", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\360\237\217\220 Deporte:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
