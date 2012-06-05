#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "qcustomplot.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    connect(ui->loadButton, SIGNAL(clicked()), this, SLOT(loadImage()));
    connect(ui->histButton, SIGNAL(clicked()), this, SLOT(showHistogram()));
    this->currentImage = new QImage();
//    ui->customPlot->addGraph();
}

MainWindow::~MainWindow(){
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

void MainWindow::showHistogram(){
    QDialog histogramDialog;//will have to inherit from this in order to display the graph
    QCustomPlot customPlot;
    customPlot.addGraph();
    histogramDialog.exec();
}

//void MainWindow::drawGraph(){
//    QVector<double> x(101), y(101);
//    for(int i=0;i<101;i++){
//        x[i] = i - 50;
//        y[i] = x[i] * x[i];
//    }
//    ui->customPlot->addGraph();
//    ui->customPlot->graph(0)->setData(x,y);
//    ui->customPlot->xAxis->setLabel("x");
//    ui->customPlot->yAxis->setLabel("y");
//    ui->customPlot->xAxis->setRange(-50, 50);
//    ui->customPlot->yAxis->setRange(0, 2500);
//    ui->customPlot->replot();
//}
