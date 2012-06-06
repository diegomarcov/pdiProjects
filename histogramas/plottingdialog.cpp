#include "plottingdialog.h"
#include "ui_plottingdialog.h"
#include <QRgb>

PlottingDialog::PlottingDialog(QWidget *parent) : QDialog(parent), ui(new Ui::PlottingDialog)
{
    ui->setupUi(this);
    ui->customPlot->addGraph();
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
    for(int i = 0;i<16;i++){
        valueRData[i] = valueRData[i] / (double)totalPix;
        valueGData[i] = valueRData[i] / (double)totalPix;
        valueBData[i] = valueRData[i] / (double)totalPix;
    }
    rBar->setData(keyRData, valueRData);
    gBar->setData(keyGData, valueGData);
    bBar->setData(keyBData, valueBData);
    ui->customPlot->xAxis->setAutoTicks(false);
    QStringList tickNames;
    char buffer[4] = "";
    for (int i=0;i<255;i=i+16){
        QString name;
        qDebug() << "Calling itoa with " << i << buffer << 10;
        name.append(itoa(i,buffer, 10));
        name.append("-");
        name.append(itoa(i+15,buffer,10));
        qDebug() << "Appending" << name;
        tickNames << name;
    }

    qDebug() << "Creating list with " << tickNames;
    QVector<QString> vect = QVector<QString>::fromList(tickNames);
    qDebug() << "Auto tick step to false";
    ui->customPlot->xAxis->setAutoTickStep(false);
    ui->customPlot->xAxis->setTickStep(1);
    qDebug() << "Tick step = 1";
    ui->customPlot->xAxis->setRange(0,16);
    qDebug() << "Tick labels";
    ui->customPlot->xAxis->setTickVectorLabels(&vect);
    qDebug() << "Range";
    ui->customPlot->yAxis->setRange(0,1);
    ui->customPlot->yAxis->setTickStep(0.1);
    ui->customPlot->replot();
    qDebug() << "Replotting";
}
