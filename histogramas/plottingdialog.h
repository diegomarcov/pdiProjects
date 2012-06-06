#ifndef PLOTTINGDIALOG_H
#define PLOTTINGDIALOG_H

#include <QDialog>

namespace Ui {
class PlottingDialog;
}

class PlottingDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit PlottingDialog(QWidget *parent = 0);
    ~PlottingDialog();
    void drawHistogram(QImage *image);
    
private:
    Ui::PlottingDialog *ui;
};

#endif // PLOTTINGDIALOG_H
