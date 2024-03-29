#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "imgoperations.h"

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
    void loadImage1();
    void loadImage2();
    void applyOperation();

private:
    Ui::MainWindow *ui;
    QImage *loadImage();
    QImage *currentFirstImage;
    QImage *currentSecondImage;
    ImgOperations imgOps;
};

#endif // MAINWINDOW_H
