#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    createConnections();
    //setDefaultValues();
    ui->graphicsView->setScene(&scene);
    scene.setBackgroundBrush(QBrush(currentColor));
}

void MainWindow::createConnections(){
    connect(ui->sliderR, SIGNAL(sliderMoved(int)), this, SLOT(changeRValue(int)));
    connect(ui->sliderG, SIGNAL(sliderMoved(int)), this, SLOT(changeGValue(int)));
    connect(ui->sliderB, SIGNAL(sliderMoved(int)), this, SLOT(changeBValue(int)));
    connect(ui->sliderH, SIGNAL(sliderMoved(int)), this, SLOT(changeHValue(int)));
    connect(ui->sliderS, SIGNAL(sliderMoved(int)), this, SLOT(changeSValue(int)));
    connect(ui->sliderV, SIGNAL(sliderMoved(int)), this, SLOT(changeVValue(int)));
}

void MainWindow::setDefaultValues(){
    QColor hsvColor = currentColor.toHsv();
    ui->sliderH->setValue(hsvColor.hsvHue());
    ui->sliderS->setValue(hsvColor.hsvSaturation());
    ui->sliderV->setValue(hsvColor.lightness());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeRValue(int r){
    currentColor.setRed(r);
    scene.setBackgroundBrush(QBrush(currentColor));
    qDebug() << currentColor;
    updateSliders();
}

void MainWindow::changeGValue(int g){
    currentColor.setGreen(g);
    scene.setBackgroundBrush(QBrush(currentColor));
    qDebug() << currentColor;
    updateSliders();
}

void MainWindow::changeBValue(int b){
    currentColor.setBlue(b);
    scene.setBackgroundBrush(QBrush(currentColor));
    qDebug() << currentColor;
    updateSliders();
}

void MainWindow::changeHValue(int h){
    qDebug() << "Starting to change Hue...";
    qDebug() << "Current color: RGB " << currentColor.red() << currentColor.green() << currentColor.blue();
    QColor hsvColor = currentColor.toHsv();
    qDebug() << "HSV Color is now:" << hsvColor.hue() << hsvColor.saturation() << hsvColor.value();
    qDebug() << "Which in RGB is: " << hsvColor.red() << hsvColor.green() << hsvColor.blue();
    qDebug() << "Now setting hue to " << h;
    hsvColor.setHsv(h, hsvColor.saturation(), hsvColor.value());
    qDebug() << "HSV Color is now:" << hsvColor.hue() << hsvColor.saturation() << hsvColor.value();
    currentColor = hsvColor/*.toRgb()*/;
    qDebug() << "Current color: RGB " << currentColor.red() << currentColor.green() << currentColor.blue();
    qDebug() << "Finished changing hue!";
    scene.setBackgroundBrush(QBrush(currentColor));
    updateSliders();
}

void MainWindow::changeSValue(int s){
    qDebug() << "Starting to change Saturation...";
    qDebug() << "Current color: RGB " << currentColor.red() << currentColor.green() << currentColor.blue();
    QColor hsvColor = currentColor.toHsv();
    qDebug() << "HSV Color is now:" << hsvColor.hue() << hsvColor.saturation() << hsvColor.value();
    qDebug() << "Which in RGB is: " << hsvColor.red() << hsvColor.green() << hsvColor.blue();
    qDebug() << "Now setting saturation to " << s;
    hsvColor.setHsv(hsvColor.hue(), s, hsvColor.value());
    qDebug() << "HSV Color is now:" << hsvColor.hue() << hsvColor.saturation() << hsvColor.value();
    currentColor = hsvColor;
    qDebug() << "Current color: RGB " << currentColor.red() << currentColor.green() << currentColor.blue();
    qDebug() << "Finished changing saturation!";
    qDebug() << "Changing slider...";
    scene.setBackgroundBrush(QBrush(currentColor));
    updateSliders();
}

void MainWindow::changeVValue(int v){
    QColor hsvColor = currentColor.toHsv();
    hsvColor.setHsv(currentColor.hue(), currentColor.saturation(), v);
    currentColor = hsvColor;
    qDebug() << currentColor;
    scene.setBackgroundBrush(QBrush(currentColor));
    updateSliders();
}

void MainWindow::updateSliders(){
    ui->sliderR->setValue(this->currentColor.red());
    ui->sliderG->setValue(this->currentColor.green());
    ui->sliderB->setValue(this->currentColor.blue());
    ui->sliderH->setValue(this->currentColor.hue());
    ui->sliderS->setValue(this->currentColor.saturation());
    ui->sliderV->setValue(this->currentColor.value());
}
