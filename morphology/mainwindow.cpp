#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    this->currentFirstImage = new QImage();
    this->currentSecondImage = new QImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::setImageOnLabel(QImage *img, QLabel *label){
    int height = (label->maximumHeight() < img->height()) ? label->maximumHeight() : img->height();
    int width = (label->maximumWidth() < img->width())?  label->maximumWidth() : img->width();
    label->setPixmap(QPixmap::fromImage(img->scaled(QSize(width, height))));
}


void MainWindow::on_transferButton_clicked()
{
    delete this->currentFirstImage;
    this->currentFirstImage = new QImage(*this->currentSecondImage);
    setImageOnLabel(this->currentSecondImage, ui->imageLabel);
}

void MainWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Seleccione la imagen", QDir::currentPath());
    if (!fileName.isEmpty()) {
        delete this->currentFirstImage;
        this->currentFirstImage = new QImage(fileName);
        if (this->currentFirstImage->isNull()) {
            QMessageBox::information(this, "Morfología", "No se puede abrir el archivo!");
            return;
        }
        setImageOnLabel(this->currentFirstImage, ui->imageLabel);
    }
}
