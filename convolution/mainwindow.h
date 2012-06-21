#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imgconvolutions.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
public slots:
    void loadImage();
    void applyFilter();

private slots:
    void on_sizeSpinBox_valueChanged(int arg1);

private:
    Ui::MainWindow *ui;
    QImage *currentImage;
    ImgConvolutions convolutions;
};

#endif // MAINWINDOW_H
