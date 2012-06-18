#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadImage()));
    this->currentImage = new QImage();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::loadImage(){
    QString fileName = QFileDialog::getOpenFileName(this, "Seleccione la imagen", QDir::currentPath());
    if (!fileName.isEmpty()) {
        delete this->currentImage;
        this->currentImage = new QImage(fileName);
        if (this->currentImage->isNull()) {
            QMessageBox::information(this, "Histogramas", "No se puede abrir el archivo!");
            return;
        }
        int height = (ui->imageLabel->maximumHeight() < this->currentImage->height())? ui->imageLabel->maximumHeight() : this->currentImage->height();
        int width = (ui->imageLabel->maximumWidth() < this->currentImage->width())?  ui->imageLabel->maximumWidth() : this->currentImage->width();
        ui->imageLabel->setPixmap(QPixmap::fromImage(this->currentImage->scaled(QSize(width, height))));
    }
}
