#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#define MAX(a,b) ((a>b)? a : b)
#define MIN(a,b) ((a<b)? a : b)

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadImage()));
    connect(ui->applyButton, SIGNAL(clicked()), this, SLOT(applyFilter()));
    this->currentImage = new QImage();
    ui->operationComboBox->addItems(convolutions.getConvList());
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
            QMessageBox::information(this, "Convoluciones", "No se puede abrir el archivo!");
            return;
        }
        int height = MIN(ui->imageLabel->maximumHeight(), this->currentImage->height());
        int width = MIN(ui->imageLabel->maximumWidth(), this->currentImage->width());
        ui->imageLabel->setPixmap(QPixmap::fromImage(this->currentImage->scaled(QSize(width, height))));
    }
}

void MainWindow::applyFilter(){
    int height = MIN(ui->resultLabel->maximumHeight(), this->currentImage->height());
    int width = MIN(ui->resultLabel->maximumWidth(), this->currentImage->width());
    ui->resultLabel->setPixmap(QPixmap::fromImage(convolutions.applyConvolution(
                                   ImgConvolutions::convolutionList(ui->operationComboBox->currentIndex()),
                                   this->currentImage, ui->sizeSpinBox->value()).scaled(width, height)));
}

void MainWindow::on_sizeSpinBox_valueChanged(int arg1)
{
    if(arg1 < 3){
        ui->sizeSpinBox->setValue(3);
    } else {
        if((arg1 % 2) != 1){
            ui->sizeSpinBox->setValue(arg1+1);
        }
    }
}
