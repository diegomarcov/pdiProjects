#include "imgconvolutions.h"
#include "math.h"
#include <QColor>
#include <QDebug>
//#define MAX(a,b) ((a>b)? a : b)
//#define MIN(a,b) ((a<b)? a : b)

ImgConvolutions::ImgConvolutions(){
    this->convDescriptions.insert(ImgConvolutions::CONV_PASABAJOS, "Filtro pasa bajos");
    this->convDescriptions.insert(ImgConvolutions::CONV_PASAALTOS, "Pasa altos");
    this->convDescriptions.insert(ImgConvolutions::CONV_BARTLETT, "Filtro Bartlett");
    this->convDescriptions.insert(ImgConvolutions::CONV_GAUSSIANO, "Filtro Gaussiano");
    this->convDescriptions.insert(ImgConvolutions::CONV_SHARPEN, "Image Sharpening");
    this->convDescriptions.insert(ImgConvolutions::CONV_MOTIONBLUR, "Motion Blur");
    this->convDescriptions.insert(ImgConvolutions::CONV_SOBEL, "Filtro Sobel");
    this->convDescriptions.insert(ImgConvolutions::CONV_PA_LPv4, "Laplaciano 4 vecinos");
    this->convDescriptions.insert(ImgConvolutions::CONV_PA_LPv8, "Laplaciano 8 vecinos");
}

QStringList ImgConvolutions::getConvList(){
    QHash<convolutionList, QString>::const_iterator i;
    QStringList ops;
    for(i = this->convDescriptions.constBegin(); i != this->convDescriptions.constEnd(); ++i){
        ops << i.value();
    }
    return ops;
}

QImage ImgConvolutions::applyConvolution(convolutionList op, QImage *img1, int filterSize){
    switch(op){
        case CONV_PASABAJOS:
            return pasaBajos(img1, filterSize);
        case CONV_BARTLETT:
        case CONV_GAUSSIANO:
        case CONV_SHARPEN:
            return sharpen(img1, filterSize);
        case CONV_MOTIONBLUR:
            return motionBlur(img1, filterSize);
        case CONV_PASAALTOS:
            return pasaAltos(img1, filterSize);
        case CONV_SOBEL:
            return sobel(img1);
        case CONV_PA_LPv4:
        case CONV_PA_LPv8:
            return QImage();
    }
    return QImage();
}

inline QColor ImgConvolutions::getColor(QPoint currentPixel, QPoint offset, QImage *img) const{
    return QColor(img->pixel((currentPixel.x() + offset.x() + img->width()) % img->width(),
                      (currentPixel.y() + offset.y() + img->height()) % img->height()));
}

QImage ImgConvolutions::sobel(QImage *img){
    QImage ret = QImage(img->width(), img->height(), img->format());
    qDebug() << "Applying Sobel";
    int currentR, currentG, currentB;
    int alphaRed, betaRed, alphaGreen, betaGreen, alphaBlue, betaBlue;
    QColor a0, a1, a2, a3, a4, a5, a6, a7;
    QColor resultPixel;
    for (int x = 0; x < img->width(); x++){
        for (int y = 0;y < img->height(); y++){
        //double FOR in order to iterate on the image;
            currentR = 0;
            currentG = 0;
            currentB = 0;

            //alpha = (a2 + 2a3 + a4) - (a0 + 2a7 + a6)
            //beta =  (a0 + 2a1 + a2) - (a6 + 2a5 + a4)
            //current = sqrt(alpha**2 + beta**2)
            //  a0  a1  a2
            //  a7  g   a3
            //  a6  a5  a4
            QPoint origin = QPoint(x,y);
            a0 = getColor(origin, QPoint(-1,-1), img);
            a1 = getColor(origin, QPoint(0,-1), img);
            a2 = getColor(origin, QPoint(1,-1), img);
            a3 = getColor(origin, QPoint(1,0), img);
            a4 = getColor(origin, QPoint(1,1), img);
            a5 = getColor(origin, QPoint(0,1), img);
            a6 = getColor(origin, QPoint(-1,1), img);
            a7 = getColor(origin, QPoint(-1,0), img);

            alphaRed = (a2.red() + 2 * a3.red() + a4.red()) - (a0.red() + 2 * a7.red() + a6.red());
            betaRed  = (a0.red() + 2 * a1.red() + a2.red()) - (a6.red() + 2 * a5.red() + a4.red());

            alphaBlue = (a2.blue() + 2 * a3.blue() + a4.blue()) - (a0.blue() + 2 * a7.blue() + a6.blue());
            betaBlue  = (a0.blue() + 2 * a1.blue() + a2.blue()) - (a6.blue() + 2 * a5.blue() + a4.blue());

            alphaGreen = (a2.green() + 2 * a3.green() + a4.green()) - (a0.green() + 2 * a7.green() + a6.green());
            betaGreen  = (a0.green() + 2 * a1.green() + a2.green()) - (a6.green() + 2 * a5.green() + a4.green());

            currentR = std::min(std::max(int(sqrt(alphaRed * alphaRed + betaRed * betaRed)), 0), 255);
            currentG = std::min(std::max(int(sqrt(alphaGreen * alphaGreen + betaGreen * betaGreen)), 0), 255);
            currentB = std::min(std::max(int(sqrt(alphaBlue * alphaBlue + betaBlue * betaBlue)), 0), 255);
            resultPixel.setRgb(currentR, currentG, currentB);
//            qDebug() << x << y << ret.width() << ret.height();
            ret.setPixel(x, y, resultPixel.rgb());
        }
    }
    return ret;
}

QImage ImgConvolutions::motionBlur(QImage *img, int filterSize){
    QVector<double> filterMatrix(filterSize * filterSize);
    filterMatrix.fill(0.0);
    for(int i = 0; i < filterSize; i++){
        filterMatrix[(i * filterSize) + i] = 1.0;
    }
    qDebug() << "Applying motion blur";
    QImage ret = applyMatrix(img, filterMatrix, 1.0/filterSize);
    return ret;
}

QImage ImgConvolutions::sharpen(QImage *img, int filterSize){
    int matrixSize = filterSize * filterSize;
    QVector<double> filterMatrix(matrixSize);
    filterMatrix.fill(-1.0);
    filterMatrix[matrixSize/2] = matrixSize;
    qDebug() << "Applying sharpening";
    QImage ret = applyMatrix(img, filterMatrix);
    return ret;
}

QImage ImgConvolutions::pasaBajos(QImage *img, int filterSize){
    int matrixSize = filterSize * filterSize;
    QVector<double> filterMatrix(matrixSize);
    filterMatrix.fill(1.0);
    qDebug() << "Applying low-frequency filter";
    QImage ret = applyMatrix(img, filterMatrix, 1.0/matrixSize);
    return ret;
}

QImage ImgConvolutions::pasaAltos(QImage *img, int filterSize){
    int matrixSize = filterSize * filterSize;
    QVector<double> filterMatrix(matrixSize);
    filterMatrix.fill(-1.0);
    filterMatrix[matrixSize/2] = matrixSize - 1;
    qDebug() << "Applying high-frequency filter";
    QImage ret = applyMatrix(img, filterMatrix);
    return ret;
}

QImage ImgConvolutions::applyMatrix(QImage *img, QVector<double> matrix, double factor, double bias){
    QImage ret = QImage(img->width(), img->height(), img->format());
    int rowSize = sqrt(matrix.size());
    qDebug() << "Applying filter:" << matrix;
    qDebug() << "Using factor" << factor << "and bias" << bias;
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
            currentR = std::min(std::max(int(((currentR * factor) + bias)), 0), 255);
            currentG = std::min(std::max(int(((currentG * factor) + bias)), 0), 255);
            currentB = std::min(std::max(int(((currentB * factor) + bias)), 0), 255);
            resultPixel.setRgb(currentR, currentG, currentB);
//            qDebug() << x << y << ret.width() << ret.height();
            ret.setPixel(x, y, resultPixel.rgb());
        }
    }
    return ret;
}
