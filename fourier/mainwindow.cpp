#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fft.h"
#include "complex.h"
#include <QImage>
#include <QPixmap>
#include <QColor>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QImage img = QImage("dot.png");
    ui->imgLabel->setPixmap(QPixmap::fromImage(img.scaled(ui->imgLabel->maximumSize())));
    sleep(1);
    int w = img.width();
    int h = img.height();
    int total = w*h;
    complex *imgComplex = new complex[total];
    complex *output = new complex[total];
    qDebug() << "FFFFFFFFUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUURIER";
    qDebug() << w*h;
    sleep(1);
    for (int x = 0; x < w; x++) {
        for(int y = 0; y < h; y++){
            qDebug() << "Pixel " << x << y;
            imgComplex[(x*w) + y] = complex(QColor(img.pixel(x,y)).value(), 0);
        }
    }
    sleep(1);
    qDebug() << "FFFFFFFFUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUURIER";
    CFFT::Forward(imgComplex, output, w*h);
    qDebug() << "FFFFFFFFUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUUURIER";
    sleep(1);
    QImage result = QImage(w, h, img.format());
    for (int x = 0; x < w; x++) {
        for(int y = 0; y < h; y++) {
            result.setPixel(x, y, output[(x*w) + y].re());
        }
    }
    sleep(1);
    delete[] imgComplex;
    delete[] output;
    //sleep(1);
    ui->resultLabel->setPixmap(QPixmap::fromImage(result.scaled(ui->resultLabel->maximumSize())));
}

MainWindow::~MainWindow()
{
    delete ui;
}
