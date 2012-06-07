#include "plottingdialog.h"
#include "ui_plottingdialog.h"
#include <QRgb>
#include <cstdio>

PlottingDialog::PlottingDialog(QWidget *parent) : QDialog(parent), ui(new Ui::PlottingDialog)
{
    ui->setupUi(this);
}

PlottingDialog::~PlottingDialog()
{
    delete ui;
}

void PlottingDialog::drawHistogram(QImage *img){
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

    qDebug() << "Creating list with " << tickNames;
    QVector<QString> vect = QVector<QString>::fromList(tickNames);
    qDebug() << "Auto tick step to false";
    ui->customPlot->legend->setVisible(true);
    ui->customPlot->xAxis->setRange(0,17);
    ui->customPlot->xAxis->setAutoTicks(false);
    ui->customPlot->xAxis->setAutoTickStep(false);
    ui->customPlot->xAxis->setTickStep(1);
    ui->customPlot->xAxis->setAutoSubTicks(true);
    ui->customPlot->xAxis->setAutoTickLabels(false);
    qDebug() << "Tick vector" << tickVector;
    qDebug() << "Tick names" << tickNames;
    ui->customPlot->xAxis->setTickVector(&tickVector, true);
    qDebug() << "My tick vector is: " << *(ui->customPlot->xAxis->tickVector());
    ui->customPlot->xAxis->setTickVectorLabels(&vect, true);
    qDebug() << "My label vector is: " << *(ui->customPlot->xAxis->tickVectorLabels());
    qDebug() << "Range";
    ui->customPlot->yAxis->setRange(0,1);
//    ui->customPlot->yAxis->setTickStep(0.1);
    ui->customPlot->replot();
    qDebug() << "Replotting";
}
