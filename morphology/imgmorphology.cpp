#include "imgmorphology.h"
#include <QColor>
#include <QDebug>
ImgMorphology::ImgMorphology()
{
    this->morphDescriptions.insert(ImgMorphology::MORPH_DILATE, "Dilatacion");
    this->morphDescriptions.insert(ImgMorphology::MORPH_ERODE, "Erosion");
}

inline QColor ImgMorphology::getColor(QPoint currentPixel, QPoint offset, QImage *img) const{
    return QColor(img->pixel((currentPixel.x() + offset.x() + img->width()) % img->width(),
                      (currentPixel.y() + offset.y() + img->height()) % img->height()));
}

QImage ImgMorphology::applyOperation(QImage *img, morphologyList operation, int filterSize, int iterations = 1){
    switch(operation){
        case MORPH_DILATE:
            return dilate(img, filterSize, iterations);
        case MORPH_ERODE:
            return erode(img, filterSize, iterations);
    }
    return QImage();
}

QStringList ImgMorphology::getOperationList(){
    QHash<morphologyList, QString>::const_iterator i;
    QStringList ops;
    for(i = this->morphDescriptions.constBegin(); i != this->morphDescriptions.constEnd(); ++i){
        ops << i.value();
    }
    return ops;
}

QImage ImgMorphology::dilate(QImage *img, int filterSize, int cantIterations){
    QImage result = QImage(img->width(), img->height(), img->format());
    QColor currentPix;
    QColor otherPix;
    QPoint origin;
    int currentR, currentG, currentB;
    QImage *orig = new QImage(*img);
    for (int iter = 0; iter < cantIterations; iter++){
        qDebug() << "Iteration number" << iter;
        for(int x=0; x < orig->width(); x++){
            for(int y=0; y < orig->height(); y++){
                currentR = 0;
                currentG = 0;
                currentB = 0;
                origin = QPoint(x,y);
                //double for to iterate on the image
                // and guess what: YAY, ANOTHER DOUBLE FOR :D
                currentPix = orig->pixel(x,y);
                for(int i=-(filterSize/2); i <= filterSize/2; i++){
                    for(int j=-(filterSize/2); j <= filterSize/2; j++){
                        otherPix = getColor(origin, QPoint(i,j), orig);
                        currentR = std::max(currentR, otherPix.red());
                        currentG = std::max(currentG, otherPix.green());
                        currentB = std::max(currentB, otherPix.blue());
                    }
                }
                result.setPixel(x, y, qRgb(currentR, currentG, currentB));
            }
        }
        delete orig;
        orig = new QImage(result);
    }
    delete orig;
    return result;
}

QImage ImgMorphology::erode(QImage *img, int filterSize, int cantIterations){
    QImage result = QImage(img->width(), img->height(), img->format());
    QColor currentPix;
    QColor otherPix;
    QPoint origin;
    int currentR, currentG, currentB;
    QImage *orig = new QImage(*img);
    for (int iter = 0; iter < cantIterations; iter++){
        qDebug() << "Iteration number" << iter;
        for(int x=0; x < orig->width(); x++){
            for(int y=0; y < orig->height(); y++){
                currentR = 255;
                currentG = 255;
                currentB = 255;
                origin = QPoint(x,y);
                //double for to iterate on the image
                // and guess what: YAY, ANOTHER DOUBLE FOR :D
                currentPix = orig->pixel(x,y);
                for(int i=-(filterSize/2); i <= filterSize/2; i++){
                    for(int j=-(filterSize/2); j <= filterSize/2; j++){
                        otherPix = getColor(origin, QPoint(i,j), orig);
                        currentR = std::min(currentR, otherPix.red());
                        currentG = std::min(currentG, otherPix.green());
                        currentB = std::min(currentB, otherPix.blue());
                    }
                }
                result.setPixel(x, y, qRgb(currentR, currentG, currentB));
            }
        }
        delete orig;
        orig = new QImage(result);
    }
    delete orig;
    return result;
}
