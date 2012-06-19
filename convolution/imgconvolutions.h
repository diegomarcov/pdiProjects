#ifndef IMGCONVOLUTIONS_H
#define IMGCONVOLUTIONS_H
#include <QHash>
#include <QImage>
#include <QStringList>
#include <QVector>

class ImgConvolutions
{
public:
    enum convolutionList {CONV_PB3, CONV_PB5, CONV_PB7, CONV_BARTLETT3, CONV_BARTLETT5, CONV_BARTLETT7,
                            CONV_GAUSS5, CONV_PA3, CONV_PA5, CONV_PA7, CONV_PA_LPv4, CONV_PA_LPv8};
    QImage applyConvolution(convolutionList op, QImage *img);
    QStringList getConvList();
    ImgConvolutions();

private:
    QHash<convolutionList, QString> convDescriptions;
    QImage pasaBajos(QImage *img, int filterSize);
    QImage pasaAltos(QImage *img, int filterSize);
    QImage applyMatrix(QImage *img, QVector<double> matrix, double factor = 1.0, double bias = 0.0);
};

#endif // IMGCONVOLUTIONS_H
