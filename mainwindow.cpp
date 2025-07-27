#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QRegularExpression>
#include <QTableWidgetItem>
#include <QVector>
#include <cstdlib>
#include <ctime>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Gestión de Atletas");
    ui->tableWidget_atletas->setEditTriggers(QAbstractItemView::NoEditTriggers);
    srand(time(nullptr));
    cargarAtletas();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::on_pushButton_registrar_clicked()
{
    QString nombre = ui->lineEdit_nombre->text();
    QString deporte = ui->comboBox_deporte->currentText();

    if(nombre.isEmpty()){
        QMessageBox::warning(this, "Campo vacío", "El nombre no puede estar vacío");
        return;

    }
    if (!idSeleccionado.isEmpty()) {
        QMessageBox::warning(this, "Operación Inválida",
                             "Ya hay un atleta seleccionado para editar.\n"
                             "Use el botón 'Actualizar' para guardar cambios, o 'Limpiar Campos' para empezar un nuevo registro.");
        return;
    }

    static const QRegularExpression regex("^[a-zA-ZñÑáéíóúÁÉÍÓÚ\\s]+$");
    if (!regex.match(nombre).hasMatch()){
        QMessageBox::warning(this, "Dato Inválido","El nombre solo puede contener letras");
        return;
    }

    Atleta nuevoAtleta;
    nuevoAtleta.id = generarNuevoId();
    nuevoAtleta.nombre = formatearNombrePropio(nombre);
    nuevoAtleta.edad = ui->spinBox_edad->value();
    nuevoAtleta.deporte = formatearNombrePropio(deporte);

    QFile archivo("atletas.txt");
    if (archivo.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&archivo);

        out << nuevoAtleta.id << ":" << nuevoAtleta.nombre << ":" << nuevoAtleta.edad << ":" << nuevoAtleta.deporte << "\n";
        archivo.close();
    } else {
        QMessageBox::critical(this, "Error de Archivo", "No se pudo abrir el archivo para registrar.");
        return;
    }

    cargarAtletas();
    ui->label_id->setText(QString::number(nuevoAtleta.id));
    ui->lineEdit_nombre->clear();
    ui->spinBox_edad->setValue(18);
    ui->comboBox_deporte->setCurrentIndex(0);
}




void MainWindow::on_tableWidget_atletas_itemClicked(QTableWidgetItem *item)
{
    if (!item) return;
    int fila = item->row();


    idSeleccionado = ui->tableWidget_atletas->item(fila, 0)->text();

    ui->label_id->setText("ID: " + idSeleccionado);
    ui->lineEdit_nombre->setText(ui->tableWidget_atletas->item(fila, 1)->text());
    ui->spinBox_edad->setValue(ui->tableWidget_atletas->item(fila, 2)->text().toInt());
    ui->comboBox_deporte->setCurrentText(ui->tableWidget_atletas->item(fila, 3)->text());
}


//Aquí va la función para limpiar campos
















//aquí va la función para el boton limpiar Campos











void MainWindow::cargarAtletas()
{
    ui->tableWidget_atletas->setColumnCount(4);
    QStringList cabeceras= {"ID", "Nombre", "Edad", "Deporte"};
    ui->tableWidget_atletas->setHorizontalHeaderLabels(cabeceras);
    ui->tableWidget_atletas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    QVector<Atleta> atletas;
    QFile archivo("atletas.txt");
    if (archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&archivo);

        while (!in.atEnd()) {
            QString linea = in.readLine();
            if(linea.isEmpty()) continue;
            QStringList separador = linea.split(':');
            if (separador.size() == 4) {
                Atleta atletaLeido;
                atletaLeido.id = separador[0].toInt();
                atletaLeido.nombre = separador[1];
                atletaLeido.edad = separador[2].toInt();
                atletaLeido.deporte = separador[3];
                atletas.append(atletaLeido);
            }
        }
        archivo.close();
    }

    ui->tableWidget_atletas->setRowCount(atletas.size());
    for (int i = 0; i < atletas.size(); ++i) {
        const auto& atleta = atletas[i];
        ui->tableWidget_atletas->setItem(i, 0, new QTableWidgetItem(QString::number(atleta.id)));
        ui->tableWidget_atletas->setItem(i, 1, new QTableWidgetItem(atleta.nombre));
        ui->tableWidget_atletas->setItem(i, 2, new QTableWidgetItem(QString::number(atleta.edad)));
        ui->tableWidget_atletas->setItem(i, 3, new QTableWidgetItem(atleta.deporte));
    }
}

//Aquí está la función para actualizar

void MainWindow::on_pushButton_actualizar_clicked()
{

    if (idSeleccionado.isEmpty()) {
        QMessageBox::warning(this, "Sin Selección", "Por favor, selecciona un atleta para actualizar.");
        return;
    }

    QString nuevoNombre = ui->lineEdit_nombre->text();
    if (nuevoNombre.isEmpty()) {
        QMessageBox::warning(this, "Campo Vacío", "El nombre no puede estar vacío.");
        return;
    }

    Atleta atletaActualizado;
    atletaActualizado.id = idSeleccionado.toInt();
    atletaActualizado.nombre = formatearNombrePropio(nuevoNombre);
    atletaActualizado.edad = ui->spinBox_edad->value();
    atletaActualizado.deporte = ui->comboBox_deporte->currentText();


    QFile archivo("atletas.txt");
    QStringList lineas;
    if (archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&archivo);
        while (!in.atEnd()) {
            lineas.append(in.readLine());
        }
        archivo.close();
    } else {
        QMessageBox::critical(this, "Error", "No se pudo leer el archivo para actualizar.");
        return;
    }


    if (archivo.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream out(&archivo);
        for (const QString &linea : lineas) {
            if (linea.startsWith(idSeleccionado + ":")) {

                out << atletaActualizado.id << ":" << atletaActualizado.nombre << ":" << atletaActualizado.edad << ":" << atletaActualizado.deporte << "\n";
            } else {

                out << linea << "\n";
            }
        }
        archivo.close();
    } else {
        QMessageBox::critical(this, "Error", "No se pudo guardar el archivo actualizado.");
        return;
    }


    cargarAtletas();
    limpiarCampos();
    QMessageBox::information(this, "Éxito", "Atleta actualizado correctamente.");
}

//Aquí va la función para eliminar










//Aquí va la función para eliminar todo el contenido de la tabla











//Aquí va la función para guardar e archivo con los atletas.txt










int MainWindow::generarNuevoId()
{
    int idAleatorio;
    bool idExiste;
    do {
        idAleatorio = 1000 + rand() % 9000;
        idExiste = false;
        QFile archivo("atletas.txt");
        if (archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QTextStream in(&archivo);
            while (!in.atEnd()) {
                QString linea = in.readLine();
                if (linea.startsWith(QString::number(idAleatorio) + ":")) {
                    idExiste = true;
                    break;
                }
            }
            archivo.close();
        }
    } while (idExiste);
    return idAleatorio;
}

QString MainWindow::formatearNombrePropio(const QString &texto)
{
    QStringList palabras = texto.split(' ', Qt::SkipEmptyParts);
    QString textoFormateado;
    for (QString &palabra : palabras) {
        if (!palabra.isEmpty()) {
            palabra = palabra.left(1).toUpper() + palabra.mid(1).toLower();
            textoFormateado += palabra + " ";
        }
    }
    return textoFormateado.trimmed();
}




