#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QTableWidgetItem>
#include <QVector>
#include <cstdlib>
#include <ctime>
#include <QFileDialog>
#include <QInputDialog>

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

    if(nombre.isEmpty() || ui->comboBox_deporte->currentIndex() == 0){
        QMessageBox::warning(this, "Campo vacío", "El nombre y el deporte no pueden estar vacíos");
        return;
    }

    if (!idSeleccionado.isEmpty()) {
        QMessageBox::warning(this, "Operación Inválida",
                             "Ya hay un atleta seleccionado para editar.\n"
                             "Usa 'Actualizar' o 'Limpiar Campos' para empezar un nuevo registro.");
        return;
    }
    for (int i = 0; i < nombre.length(); ++i) {
        QChar c = nombre[i];
        if (!c.isLetter() && !c.isSpace()) {
            QMessageBox::warning(this, "Dato Inválido", "El nombre solo puede contener letras y espacios");
            return;
        }
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
    nombreSeleccionado = ui->tableWidget_atletas->item(fila, 1)->text();

    ui->label_id->setText("ID: " + idSeleccionado);
    ui->lineEdit_nombre->setText(nombreSeleccionado);
    ui->spinBox_edad->setValue(ui->tableWidget_atletas->item(fila, 2)->text().toInt());
    ui->comboBox_deporte->setCurrentText(ui->tableWidget_atletas->item(fila, 3)->text());
}

void MainWindow::limpiarCampos()
{
    idSeleccionado.clear();
    ui->label_id->setText("ID");
    ui->lineEdit_nombre->clear();
    ui->spinBox_edad->setValue(18);
    ui->comboBox_deporte->setCurrentIndex(0);
    ui->tableWidget_atletas->clearSelection();
}

void MainWindow::on_pushButton_actualizar_clicked()
{
    const int fila=ui->tableWidget_atletas->rowCount();
    if (fila==0){
        QMessageBox::warning(this, "Vacio", "No hay atletas registrados.");
        return;
    }
    if (idSeleccionado.isEmpty()) {
        QMessageBox::warning(this, "Sin Selección", "Selecciona un atleta para actualizar.");
        return;
    }

    QString nuevoNombre = ui->lineEdit_nombre->text();
    if (nuevoNombre.isEmpty()) {
        QMessageBox::warning(this, "Campo Vacío", "El nombre no puede estar vacío.");
        return;
    }

    for (int i = 0; i < nuevoNombre.length(); ++i) {
        QChar c = nuevoNombre[i];
        if (!c.isLetter() && !c.isSpace()) {
            QMessageBox::warning(this, "Dato Inválido", "El nombre solo puede contener letras y espacios");
            return;
        }
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
            if (linea.startsWith(QString::number(atletaActualizado.id) + ":")) {
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

void MainWindow::on_pushButton_eliminar_clicked()
{
    const int fila=ui->tableWidget_atletas->rowCount();
    if (fila==0){
        QMessageBox::warning(this, "Vacio", "No hay atletas registrados.");
        return;
    }
    if (idSeleccionado.isEmpty()) {
        QMessageBox::warning(this, "Sin Selección", "Selecciona un atleta para eliminar.");
        return;
    }

    QMessageBox::StandardButton respuesta;
    respuesta = QMessageBox::question(this, "Confirmar Eliminación",
                                      "¿Seguro que quieres eliminar al atleta " + nombreSeleccionado + " con ID " + idSeleccionado +  " ?",
                                      QMessageBox::Yes | QMessageBox::No);

    if (respuesta == QMessageBox::No) return;

    QFile archivo("atletas.txt");
    QStringList lineas;

    if (archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&archivo);
        while (!in.atEnd()) {
            lineas.append(in.readLine());
        }
        archivo.close();
    } else {
        QMessageBox::critical(this, "Error", "No se pudo leer el archivo para eliminar.");
        return;
    }

    if (archivo.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text)) {
        QTextStream out(&archivo);
        for (const QString &linea : lineas) {
            if (!linea.startsWith(idSeleccionado + ":")) {
                out << linea << "\n";
            }
        }
        archivo.close();
    } else {
        QMessageBox::critical(this, "Error", "No se pudo escribir el archivo para eliminar.");
        return;
    }

    cargarAtletas();
    limpiarCampos();
    QMessageBox::information(this, "Eliminado", "Atleta eliminado correctamente.");
}

void MainWindow::cargarAtletas()
{
    ui->tableWidget_atletas->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    atletas.clear();

    QFile archivo("atletas.txt");
    if (archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&archivo);
        while (!in.atEnd()) {
            QString linea = in.readLine();
            if (linea.isEmpty()) continue;
            QStringList partes = linea.split(':');
            if (partes.size() == 4) {
                Atleta atletaLeido;
                atletaLeido.id = partes[0].toInt();
                atletaLeido.nombre = partes[1];
                atletaLeido.edad = partes[2].toInt();
                atletaLeido.deporte = partes[3];
                atletas.append(atletaLeido);
            }
        }
        archivo.close();
    }

    ui->tableWidget_atletas->setRowCount(atletas.size());

    for (int i = 0; i < atletas.size(); ++i) {
        const Atleta &a = atletas[i];
        ui->tableWidget_atletas->setItem(i, 0, new QTableWidgetItem(QString::number(a.id)));
        ui->tableWidget_atletas->setItem(i, 1, new QTableWidgetItem(a.nombre));
        ui->tableWidget_atletas->setItem(i, 2, new QTableWidgetItem(QString::number(a.edad)));
        ui->tableWidget_atletas->setItem(i, 3, new QTableWidgetItem(a.deporte));
    }
}

int MainWindow::generarNuevoId()
{
    int idAleatorio;
    bool idExiste;

    do {
        idAleatorio = 1000 + rand() % 9000;
        idExiste = false;

        for (const Atleta &a : atletas) {
            if (a.id == idAleatorio) {
                idExiste = true;
                break;
            }
        }
    } while (idExiste);

    return idAleatorio;
}

QString MainWindow::formatearNombrePropio(const QString &texto)
{
    QStringList palabras = texto.split(' ', Qt::SkipEmptyParts);
    QString resultado;
    for (QString palabra : palabras) {
        if (!palabra.isEmpty()) {
            palabra[0] = palabra[0].toUpper();
            for (int i = 1; i < palabra.length(); ++i) {
                palabra[i] = palabra[i].toLower();
            }
            resultado += palabra + " ";
        }
    }
    return resultado.trimmed();
}

void MainWindow::on_pushButton_borrarTodo_clicked()
{
    const int fila=ui->tableWidget_atletas->rowCount();
    if (fila==0){
        QMessageBox::warning(this, "Vacio", "No hay atletas registrados.");
        return;
    }

    QMessageBox::StandardButton respuesta;
    respuesta = QMessageBox::warning(this, "Confirmación",
                                     "¿Estás SEGURO que quieres borrar TODOS los atletas?",
                                     QMessageBox::Yes | QMessageBox::No);

    if (respuesta == QMessageBox::No) return;

    QFile archivo("atletas.txt");
    if (archivo.open(QIODevice::WriteOnly | QIODevice::Truncate)) {
        archivo.close();
        QMessageBox::information(this, "Completado", "Todos los datos han sido eliminados.");
    } else {
        QMessageBox::critical(this, "Error", "No se pudo borrar los datos.");
    }

    cargarAtletas();
    limpiarCampos();
}

void MainWindow::on_pushButton_guardar_clicked()
{
    if (ui->tableWidget_atletas->rowCount() == 0) {
        QMessageBox::information(this, "Tabla Vacía", "No hay atletas para guardar.");
        return;
    }

    QString nombreArchivo = QFileDialog::getSaveFileName(this, "Guardar Lista de atletas", "", "Archivos de Texto (*.txt)");

    if (nombreArchivo.isEmpty()) return;

    QFile archivo(nombreArchivo);
    if (archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&archivo);

        out << "Lista de Atletas\n";
        out << "===========================================================================\n";
        out << "ID\tNombre\t\t\t\t\tEdad\tDeporte\n";
        out << "---------------------------------------------------------------------------\n";

        for (const Atleta &a : atletas) {
            out << a.id << "\t" << a.nombre.leftJustified(30, ' ') << "\t\t" << a.edad << "\t" << a.deporte.leftJustified(20, ' ') << "\n";
        }

        archivo.close();
        QMessageBox::information(this, "Guardado", "Lista de atletas guardada correctamente.");
    } else {
        QMessageBox::critical(this, "Error", "No se pudo guardar el archivo.");
    }
}

void MainWindow::on_pushButton_limpiar_clicked()
{
    limpiarCampos();
}

void MainWindow::on_pushButton_buscar_clicked()
{
    bool ok;
    const int fila=ui->tableWidget_atletas->rowCount();
    if (fila==0){
        QMessageBox::warning(this, "Vacio", "No hay Atletas registrados.");
        return;
    }
    QString nombreBuscar = QInputDialog::getText(this, "Buscar Atleta",
                                                 "Ingrese el nombre completo del atleta:",
                                                 QLineEdit::Normal,
                                                 "", &ok);
    if (ok && nombreBuscar.isEmpty()) {
        QMessageBox::warning(this, "Campo vacío", "No escribiste nada.");
        return;
    }
    QString nombreformateado=formatearNombrePropio(nombreBuscar);
    for(int i=0;i<fila;i++){
        QString nombre=ui->tableWidget_atletas->item(i,1)->text();

        if(nombre==nombreformateado){
            QMessageBox::information(this, "Encontrado", "ID: "+ui->tableWidget_atletas->item(i,0)->text()+
            " \nNombre: "+nombreformateado+ "\nEdad: "+ui->tableWidget_atletas->item(i,2)->text()+
            "\nDeporte: "+ui->tableWidget_atletas->item(i,3)->text());
            return;
        }
    }
    QMessageBox::warning(this, "No encontrado", "No se encontro al atleta.");
}

