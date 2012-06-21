#ifndef IMGCONVOLUTIONS_H
#define IMGCONVOLUTIONS_H
#include <QHash>
#include <QImage>
#include <QStringList>
#include <QVector>

class ImgConvolutions
{
public:
    enum convolutionList {CONV_PASABAJOS, CONV_PASAALTOS, CONV_BARTLETT, CONV_GAUSSIANO, CONV_SHARPEN, CONV_MOTIONBLUR,
                          CONV_SOBEL, CONV_PA_LPv4, CONV_PA_LPv8};
    QImage applyConvolution(convolutionList op, QImage *img, int filterSize);
    QStringList getConvList();
    ImgConvolutions();

private:
    QHash<convolutionList, QString> convDescriptions;
    QColor getColor(QPoint origin, QPoint offset, QImage *img) const;
    QImage sobel(QImage *img);
    QImage pasaBajos(QImage *img, int filterSize);
    QImage sharpen(QImage *img, int filterSize);
    QImage pasaAltos(QImage *img, int filterSize);
    QImage motionBlur(QImage *img, int filterSize);
    QImage applyMatrix(QImage *img, QVector<double> matrix, double factor = 1.0, double bias = 0.0);
};

#endif // IMGCONVOLUTIONS_H
