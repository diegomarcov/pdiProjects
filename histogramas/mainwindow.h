#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void drawGraph();

public slots:
    void loadImage();
    void showRGBHistogram();
    void showLumHistogram();
    
private:
    Ui::MainWindow *ui;
    QImage *currentImage;
};

#endif // MAINWINDOW_H
