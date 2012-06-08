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
    QVector<double> keyRData(16);
    QVector<double> valueRData(16, 0);
    QVector<double> keyGData(16);
    QVector<double> valueGData(16, 0);
    QVector<double> keyBData(16);
    QVector<double> valueBData(16, 0);
    for(int i=0;i<16;i++){
        keyRData[i] = i+1;
        keyGData[i] = i+1;
        keyBData[i] = i+1;
    }
    QColor currentPixel;
    // now we can modify properties of myBars:
    for(int x=0;x<img->width();x++){
        for(int y=0;y<img->height();y++){
            currentPixel = QColor(img->pixel(x,y));
            valueRData[currentPixel.red() / 16]++;
            valueGData[currentPixel.green() / 16]++;
            valueBData[currentPixel.blue() / 16]++;
        }
    }
    rBar->setName("R Value");
    rBar->setBrush(QBrush(Qt::red));
    gBar->setName("G Value");
    gBar->setBrush(QBrush(Qt::green));
    bBar->setName("B Value");
    bBar->setBrush(QBrush(Qt::blue));
    int totalPix = img->width() * img->height();
    QVector<double> tickVector;
    for(int i = 0;i<16;i++){
        valueRData[i] = valueRData[i] / (double)totalPix;
        valueGData[i] = valueRData[i] / (double)totalPix;
        valueBData[i] = valueRData[i] / (double)totalPix;
        tickVector.append(i);
    }
    rBar->setData(keyRData, valueRData);
    gBar->setData(keyGData, valueGData);
    bBar->setData(keyBData, valueBData);
    QStringList tickNames;
    for (int i=0;i<255;i=i+16){
        QString name = QString::number(i)/* + "-" + QString::number(i+15)*/;
        qDebug() << "Appending" << name;
        tickNames << name;
    }

    QVector<QString> vect = QVector<QString>::fromList(tickNames);
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->xAxis->setRange(0,17);
    ui->customPlot->xAxis->setAutoTicks(false);
    ui->customPlot->xAxis->setAutoTickStep(false);
    ui->customPlot->xAxis->setTickStep(1);
    ui->customPlot->xAxis->setAutoSubTicks(true);
    ui->customPlot->xAxis->setAutoTickLabels(false);
    ui->customPlot->xAxis->setTickVector(&tickVector, true);
    ui->customPlot->xAxis->setTickVectorLabels(&vect, true);
    ui->customPlot->yAxis->setRange(0,1);
    ui->customPlot->replot();
    qDebug() << "Replotting";
}

void PlottingDialog::drawLumHistogram(QImage *img){
    QCPBars *lBar = new QCPBars(ui->customPlot->xAxis, ui->customPlot->yAxis);
    ui->customPlot->addPlottable(lBar);
    int bins = 10; // edit this to define the number of bins in which the histogram is separated
    QVector<double> keyLData(bins);
    QVector<double> valueLData(bins, 0);
    qreal currentLightness;
    for(int x=0;x<img->width();x++) {
        for(int y=0;y<img->height();y++){
            currentLightness = qFloor(QColor(img->pixel(x,y)).lightnessF() * bins);
            // in case luminance was exactly 1, last result would return 10!
            currentLightness = (currentLightness == bins) ? bins-1 : currentLightness;
            valueLData[currentLightness]++;
        }
    }
    QVector<QString> labelVector;
    QVector<double> tickVector;
    int totalPix = img->width() * img->height();
    for (int i=0;i<bins;i++){
        keyLData[i] = i;
        tickVector.append(i);
        labelVector.append(QString::number(i/(double) bins));
        valueLData[i] = valueLData[i] / (double) totalPix;
    }
    lBar->setData(keyLData, valueLData);
    ui->customPlot->xAxis->setLabel("Luminance %");
    ui->customPlot->xAxis->setAutoTicks(false);
    ui->customPlot->xAxis->setRange(0,bins);
    ui->customPlot->xAxis->setAutoTickStep(false);
    ui->customPlot->xAxis->setAutoSubTicks(true);
    ui->customPlot->xAxis->setAutoTickLabels(false);
    qDebug() << tickVector;
    ui->customPlot->xAxis->setTickVector(&tickVector, true);
    ui->customPlot->xAxis->setTickVectorLabels(&labelVector, true);
    ui->customPlot->yAxis->setLabel("Image %");
    ui->customPlot->yAxis->setRange(0,1);
    ui->customPlot->replot();
}
