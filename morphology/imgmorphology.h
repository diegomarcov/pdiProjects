#ifndef IMGMORPHOLOGY_H
#define IMGMORPHOLOGY_H
#include <QImage>
#include <QHash>

class ImgMorphology
{
public:
    ImgMorphology();
    enum morphologyList { MORPH_DILATE, MORPH_ERODE };
    QImage dilate(QImage *img, int filterSize, int iterations = 1);
    QImage erode(QImage *img, int filterSize, int iterations = 1);
    QStringList getOperationList();
    QImage applyOperation(QImage *img, morphologyList operation, int filterSize, int iterations);

private:
    inline QColor getColor(QPoint currentPixel, QPoint offset, QImage *img) const;
    QHash<morphologyList, QString> morphDescriptions;
};

#endif // IMGMORPHOLOGY_H
