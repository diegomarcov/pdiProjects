#ifndef IMGOPERATIONS_H
#define IMGOPERATIONS_H
#include <QStringList>
#include <QImage>
#include <QHash>

class ImgOperations
{
public:
    ImgOperations();
    enum operationList {OP_IMGSUM, OP_IMGDIFF, OP_IFDARKER, OP_IFLIGHTER};
    QImage applyOperation(operationList, QImage *img1, QImage *img2, bool applyClamping);
    QStringList getOperationList();

    QImage imgSum(QImage *img1, QImage *img2, bool applyClamping);
    QImage imgDiff(QImage *img1, QImage *img2, bool applyClamping);
    QImage ifDarker(QImage *img1, QImage *img2);
    QImage ifLighter(QImage *img1, QImage *img2);

private:
    QHash<operationList, QString> opDescriptions;
};

#endif // IMGOPERATIONS_H
