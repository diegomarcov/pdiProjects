#include "plottingdialog.h"
#include "ui_plottingdialog.h"
#include <QRgb>
#include <cstdio>
#include <qmath.h>

PlottingDialog::PlottingDialog(QWidget *parent) : QDialog(parent), ui(new Ui::PlottingDialog)
{
    ui->setupUi(this);
}

PlottingDialog::~PlottingDialog()
{
    delete ui;
}

void PlottingDialog::drawRGBHistogram(QImage *img){
    QCPBars *rBar = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *gBar = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    QCPBars *bBar = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    ui->customPlot->addPlottable(rBar);
    ui->customPlot->addPlottable(gBar);
    ui->customPlot->addPlottable(bBar);
    int bins = 16;
    QVector<double> keyRData(bins);
    QVector<double> valueRData(bins, 0);
    QVector<double> keyGData(bins);
    QVector<double> valueGData(bins, 0);
    QVector<double> keyBData(bins);
    QVector<double> valueBData(bins, 0);
    QColor currentPixel;
    int currentRed, currentGreen, currentBlue;
    // now we can modify properties of myBars:
    for(int x=0;x<img->width();x++){
        for(int y=0;y<img->height();y++){
            currentPixel = QColor(img->pixel(x,y));
            currentRed = currentPixel.redF() * bins;
            valueRData[(currentRed == bins) ? bins - 1 : currentRed]++;
            currentGreen = currentPixel.greenF() * bins;
            valueGData[(currentGreen == bins) ? bins - 1 : currentGreen]++;
            currentBlue = currentPixel.blueF() * bins;
            valueBData[(currentBlue == bins) ? bins - 1 : currentBlue]++;
        }
    }
    rBar->setName("R Value");
    rBar->setBrush(QBrush(Qt::red));
    gBar->setName("G Value");
    gBar->setBrush(QBrush(Qt::green));
    bBar->setName("B Value");
    bBar->setBrush(QBrush(Qt::blue));
    int totalPix = img->width() * img->height();
    for(int i = 0;i<bins;i++){
        keyRData[i] = (i/(double) bins);
        keyGData[i] = (i/(double) bins);
        keyBData[i] = (i/(double) bins);
        valueRData[i] = valueRData[i] / (double)totalPix;
        valueGData[i] = valueGData[i] / (double)totalPix;
        valueBData[i] = valueBData[i] / (double)totalPix;
    }
    rBar->setData(keyRData, valueRData);
    gBar->setData(keyGData, valueGData);
    bBar->setData(keyBData, valueBData);
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->xAxis->setLabel("Color %");
    ui->customPlot->xAxis->setRange(0,1);
    rBar->setWidth(1/(4*(double)bins));
    gBar->setWidth(1/(4*(double)bins));
    bBar->setWidth(1/(4*(double)bins));
    ui->customPlot->yAxis->setLabel("Image %");
    ui->customPlot->yAxis->setRange(0,1);
    ui->customPlot->replot();
    qDebug() << "Replotting";
}

void PlottingDialog::drawLumHistogram(QImage *img){
    QCPBars *lBar = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    ui->customPlot->addPlottable(lBar);
    int bins = 16; // edit this to define the number of bins in which the histogram is separated
    QVector<double> keyLData(bins);
    QVector<double> valueLData(bins, 0);
    qreal currentLightness;
    for(int x=0;x<img->width();x++) {
        for(int y=0;y<img->height();y++){
            currentLightness = qFloor(QColor(img->pixel(x,y)).lightnessF() * bins);
            //qDebug() << "CurrentLightness" << currentLightness;
            //only special case: 100% luminance -> last expression returns BINS == ilegal access!
            currentLightness = (currentLightness == bins) ? bins -1 : currentLightness;
            valueLData[currentLightness]++;
        }
    }
    int totalPix = img->width() * img->height();
    for (int i=0;i<bins;i++){
        keyLData[i] = (i/(double)bins);
        valueLData[i] = valueLData[i] / (double) totalPix;
    }
    qDebug() << keyLData;
    qDebug() << valueLData;
    lBar->setData(keyLData, valueLData);
    ui->customPlot->xAxis->setLabel("Luminance %");
    ui->customPlot->xAxis->setRange(0,1);
    lBar->setWidth(1/(2*(double)bins));
    ui->customPlot->yAxis->setLabel("Image %");
    ui->customPlot->yAxis->setRange(0,1);
    ui->customPlot->replot();
}
