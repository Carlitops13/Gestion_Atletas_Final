#include "logindialog.h"
#include "ui_logindialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

LoginDialog::LoginDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
}

LoginDialog::~LoginDialog(){
    delete ui;
}

void LoginDialog::on_pushButton_ingresar_clicked(){
    QString usuario = ui->lineEdit_usuario->text();
    QString password = ui->lineEdit_password->text();
    if (usuario.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Campos Vacíos", "Por favor, ingresa tu usuario y contraseña.");
        return;
    }
    for (int i = 0; i < usuario.length(); ++i) {
        QChar c = usuario[i];
        if (!c.isLetter()) {
            QMessageBox::warning(this, "Error de Validación", "El nombre de usuario solo debe contener letras sin espacios.");
            return;
        }
    }

    QFile file("usuarios.txt");
    if (!file.exists()) {
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);
            out << "admin:admin123";
            file.close();
        }
    }
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        bool credencialesCorrectas = false;

        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList partes = line.split(':');
            if (partes.size() == 2) {
                QString usuarioArchivo = partes[0];
                QString passwordArchivo = partes[1];
                if (usuario == usuarioArchivo && password == passwordArchivo) {
                    credencialesCorrectas = true;
                    break;
                }
            }
        }
        file.close();

        if (credencialesCorrectas) {
            accept();
        } else {
            QMessageBox::critical(this, "Error de Inicio de Sesión", "Usuario o contraseña incorrectos.");
        }
    }
}
