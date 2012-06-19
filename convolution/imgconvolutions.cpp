#include "imgconvolutions.h"
#include "math.h"
#include <QColor>
#include <QDebug>
//#define MAX(a,b) ((a>b)? a : b)
//#define MIN(a,b) ((a<b)? a : b)

ImgConvolutions::ImgConvolutions(){
    this->convDescriptions.insert(ImgConvolutions::CONV_PB3, "Pasa bajos 3x3");
    this->convDescriptions.insert(ImgConvolutions::CONV_PB5, "Pasa bajos 5x5");
    this->convDescriptions.insert(ImgConvolutions::CONV_PB7, "Pasa bajos 7x7");
    this->convDescriptions.insert(ImgConvolutions::CONV_BARTLETT3, "Bartlett 3x3");
    this->convDescriptions.insert(ImgConvolutions::CONV_BARTLETT5, "Bartlett 5x5");
    this->convDescriptions.insert(ImgConvolutions::CONV_BARTLETT7, "Bartlett 7x7");
    this->convDescriptions.insert(ImgConvolutions::CONV_GAUSS5, "Filtro Gaussiano 5x5");
    this->convDescriptions.insert(ImgConvolutions::CONV_PA3, "Pasa altos 3x3");
    this->convDescriptions.insert(ImgConvolutions::CONV_PA5, "Pasa altos 5x5");
    this->convDescriptions.insert(ImgConvolutions::CONV_PA7, "Pasa altos 7x7");
    this->convDescriptions.insert(ImgConvolutions::CONV_PA_LPv4, "Laplaciano 4 vecinos");
    this->convDescriptions.insert(ImgConvolutions::CONV_PA_LPv8, "Laplaciano 8x8");
}

QStringList ImgConvolutions::getConvList(){
    QHash<convolutionList, QString>::const_iterator i;
    QStringList ops;
    for(i = this->convDescriptions.constBegin(); i != this->convDescriptions.constEnd(); ++i){
        ops << i.value();
    }
    return ops;
}

QImage ImgConvolutions::applyConvolution(convolutionList op, QImage *img1){
    switch(op){
        case CONV_PB3:
            return pasaBajos(img1, 3);
        case CONV_PB5:
            return pasaBajos(img1, 5);
        case CONV_PB7:
            return pasaBajos(img1, 7);
        case CONV_BARTLETT3:
        case CONV_BARTLETT5:
        case CONV_BARTLETT7:
        case CONV_GAUSS5:
        case CONV_PA3:
            return pasaAltos(img1, 3);
        case CONV_PA5:
            return pasaAltos(img1, 5);
        case CONV_PA7:
            return pasaAltos(img1, 7);
        case CONV_PA_LPv4:
        case CONV_PA_LPv8:
        return QImage();
    }
    return QImage();
}

QImage ImgConvolutions::pasaBajos(QImage *img, int filterSize){
    int matrixSize = filterSize * filterSize;
    QVector<double> filterMatrix(matrixSize);
    filterMatrix.fill(1.0);
    qDebug() << "Applying filter:" << filterMatrix;
    QImage ret = applyMatrix(img, filterMatrix);
    return ret;
}

QImage ImgConvolutions::pasaAltos(QImage *img, int filterSize){
    int matrixSize = filterSize * filterSize;
    QVector<double> filterMatrix(matrixSize);
    filterMatrix.fill(-1.0);
    filterMatrix[matrixSize/2] = matrixSize - 1;
    qDebug() << "Applying filter:" << filterMatrix;
    QImage ret = applyMatrix(img, filterMatrix);
    return ret;
}

QImage ImgConvolutions::applyMatrix(QImage *img, QVector<double> matrix, double factor, double bias){
    QImage ret = QImage(img->width(), img->height(), img->format());
    int rowSize = sqrt(matrix.size());
    //Note: this is ONLY going to work because rowSize should be an odd number.
    //Do NOT deposit your faith on this. I mean, you shouldn't deposit your faith
    //on anything, but SPECIALLY not this.
    int rowBeginning = rowSize / 2;
    int currentX, currentY, currentR, currentG, currentB;
    QColor currentPixel;
    QColor resultPixel;
    for (int x = 0; x < img->width(); x++){
        for (int y = 0;y < img->height(); y++){
        //double FOR in order to iterate on the image;
            currentR = 0;
            currentG = 0;
            currentB = 0;
            for(int i = 0; i < rowSize; i++){
                for(int j = 0; j < rowSize; j++){
                    //now iterating into the matrix for each pixel
                    //BTW: this is O(scary)
                    currentX = ((x - rowBeginning + i + img->width()) % img->width());
                    currentY = ((y - rowBeginning + j + img->height()) % img->height());
                    currentPixel = QColor(img->pixel(currentX, currentY));
                    currentR += currentPixel.red() * matrix[(i * rowSize) + j];
                    currentG += currentPixel.green() * matrix[(i * rowSize) + j];
                    currentB += currentPixel.blue() * matrix[(i * rowSize) + j];
                }
            }
            currentR = std::min(std::max(int(((currentR * factor) + bias) / matrix.size()), 0), 255);
            currentG = std::min(std::max(int(((currentG * factor) + bias) / matrix.size()), 0), 255);
            currentB = std::min(std::max(int(((currentB * factor) + bias) / matrix.size()), 0), 255);
            resultPixel.setRgb(currentR, currentG, currentB);
//            qDebug() << x << y << ret.width() << ret.height();
            ret.setPixel(x, y, resultPixel.rgb());
        }
    }
    return ret;
}
