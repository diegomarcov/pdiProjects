#include "imgoperations.h"
#define CLAMP_SUM(a,b) ((a+b > 255)?255 : a+b)
#define CLAMP_DIFF(a,b) ((a-b < 0)?0 : a-b)
#define MIN(a,b) ((a<b)?a:b)
#define MAX(a,b) ((a>b)?a:b)
#include <QColor>
#include <QDebug>

ImgOperations::ImgOperations()
{
    this->opDescriptions.insert(ImgOperations::OP_IMGSUM, "Suma de imagenes");
    this->opDescriptions.insert(ImgOperations::OP_IMGDIFF, "Resta de imagenes");
    this->opDescriptions.insert(ImgOperations::OP_IFDARKER, "If-Darker");
    this->opDescriptions.insert(ImgOperations::OP_IFLIGHTER, "If-Lighter");
}

QImage ImgOperations::applyOperation(operationList op, QImage *img1, QImage *img2){
    qDebug() << "Applying operation " << op;
    switch(op){
        case OP_IMGSUM:
            return imgSum(img1, img2);
        case OP_IMGDIFF:
            return imgDiff(img1, img2);
        case OP_IFDARKER:
            return ifDarker(img1, img2);
        case OP_IFLIGHTER:
            return ifLighter(img1, img2);
    }
    return QImage();
}

QImage ImgOperations::imgSum(QImage *img1, QImage *img2){
    int w1 = img1->width();
    int w2 = img2->width();
    int h1 = img1->height();
    int h2 = img2->height();
    QImage result = QImage(w1, h1, QImage::Format_RGB16);
    QColor pix1;
    QColor pix2;
    QRgb resultPix;
    if((h1 == h2) && (w1 == w2)){
        for (int x = 0; x < w1; x++){
            for (int y = 0; y < h1; y++){
                pix1.setRgb(img1->pixel(x,y));
                pix2.setRgb(img2->pixel(x,y));
                resultPix = qRgb(CLAMP_SUM(pix1.red(), pix2.red()), CLAMP_SUM(pix1.green(), pix2.green()), CLAMP_SUM(pix1.blue(), pix2.blue()));
                result.setPixel(x, y, resultPix);
            }
        }
    }
    return result;
}

QImage ImgOperations::imgDiff(QImage *img1, QImage *img2){
    int w1 = img1->width();
    int w2 = img2->width();
    int h1 = img1->height();
    int h2 = img2->height();
    QImage result = QImage(w1, h1, QImage::Format_RGB16);
    QColor pix1;
    QColor pix2;
    QRgb resultPix;
    if((h1 == h2) && (w1 == w2)){
        for (int x = 0; x < w1; x++){
            for (int y = 0; y < h1; y++){
                pix1.setRgb(img1->pixel(x,y));
                pix2.setRgb(img2->pixel(x,y));
                resultPix = qRgb(CLAMP_DIFF(pix1.red(), pix2.red()), CLAMP_DIFF(pix1.green(), pix2.green()), CLAMP_DIFF(pix1.blue(), pix2.blue()));
                result.setPixel(x, y, resultPix);
            }
        }
    }
    return result;
}

QImage ImgOperations::ifDarker(QImage *img1, QImage *img2){
    int w1 = img1->width();
    int w2 = img2->width();
    int h1 = img1->height();
    int h2 = img2->height();
    QImage result = QImage(w1, h1, QImage::Format_RGB16);
    QColor pix1;
    QColor pix2;
    QRgb resultPix;
    if((h1 == h2) && (w1 == w2)){
        for (int x = 0; x < w1; x++){
            for (int y = 0; y < h1; y++){
                pix1.setRgb(img1->pixel(x,y));
                pix2.setRgb(img2->pixel(x,y));
                resultPix = qRgb(MIN(pix1.red(), pix2.red()), MIN(pix1.green(), pix2.green()), MIN(pix1.blue(), pix2.blue()));
                result.setPixel(x, y, resultPix);
            }
        }
    }
    return result;
}

QImage ImgOperations::ifLighter(QImage *img1, QImage *img2){
    int w1 = img1->width();
    int w2 = img2->width();
    int h1 = img1->height();
    int h2 = img2->height();
    QImage result = QImage(w1, h1, QImage::Format_RGB16);
    QColor pix1;
    QColor pix2;
    QRgb resultPix;
    if((h1 == h2) && (w1 == w2)){
        for (int x = 0; x < w1; x++){
            for (int y = 0; y < h1; y++){
                pix1.setRgb(img1->pixel(x,y));
                pix2.setRgb(img2->pixel(x,y));
                resultPix = qRgb(MAX(pix1.red(), pix2.red()), MAX(pix1.green(), pix2.green()), MAX(pix1.blue(), pix2.blue()));
                result.setPixel(x, y, resultPix);
            }
        }
    }
    return result;
}


QStringList ImgOperations::getOperationList(){
    QHash<operationList, QString>::const_iterator i;
    QStringList ops;
    for(i = this->opDescriptions.constBegin(); i != this->opDescriptions.constEnd(); ++i){
        ops << i.value();
    }
    return ops;
}
