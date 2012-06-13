#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDir>
#include <QMessageBox>
#include <QDebug>
#include "imgoperations.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadImage1()));
    connect(ui->loadButton2, SIGNAL(clicked()), this, SLOT(loadImage2()));
    connect(ui->applyButton, SIGNAL(clicked()), this, SLOT(applyOperation()));
    this->imgOps = ImgOperations();
    ui->operationComboBox->addItems(this->imgOps.getOperationList());
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::applyOperation(){
    if (this->currentFirstImage->size() == this->currentSecondImage->size()){
        QImage result = this->imgOps.applyOperation(ImgOperations::operationList(this->ui->operationComboBox->currentIndex()), this->currentFirstImage, this->currentSecondImage, ui->clampCheckBox->isChecked());
        int height = (ui->imageLabel->maximumHeight() < result.height())? ui->imageLabel->maximumHeight() : result.height();
        int width = (ui->imageLabel->maximumWidth() < result.width())?  ui->imageLabel->maximumWidth() : result.width();
        ui->resultLabel->setPixmap(QPixmap::fromImage(result.scaled(QSize(width, height))));
    } else {
        QMessageBox::information(this, "Img Operations", "Las imagenes tienen diferente tamaño!");
    }
}

QImage* MainWindow::loadImage(){
    QString fileName = QFileDialog::getOpenFileName(this, "Seleccione la imagen", QDir::currentPath());
    if (!fileName.isEmpty()) {
        QImage *currentImage = new QImage(fileName);
        if (currentImage->isNull()) {
            QMessageBox::information(this, "Img Operations", "No se puede abrir el archivo!");
            return NULL;
        }
        return currentImage;
    }
    else return NULL;
}


void MainWindow::loadImage1(){
    this->currentFirstImage = loadImage();
    int height = (ui->imageLabel->maximumHeight() < this->currentFirstImage->height())? ui->imageLabel->maximumHeight() : this->currentFirstImage->height();
    int width = (ui->imageLabel->maximumWidth() < this->currentFirstImage->width())?  ui->imageLabel->maximumWidth() : this->currentFirstImage->width();
    ui->imageLabel->setPixmap(QPixmap::fromImage(this->currentFirstImage->scaled(QSize(width, height))));
}

void MainWindow::loadImage2(){
    this->currentSecondImage = loadImage();
    int height = (ui->imageLabel2->maximumHeight() < this->currentSecondImage->height())? ui->imageLabel2->maximumHeight() : this->currentSecondImage->height();
    int width = (ui->imageLabel2->maximumWidth() < this->currentSecondImage->width())?  ui->imageLabel2->maximumWidth() : this->currentSecondImage->width();
    ui->imageLabel2->setPixmap(QPixmap::fromImage(this->currentSecondImage->scaled(QSize(width, height))));
}
