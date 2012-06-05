#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsView>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    QWidget *central;
    void setup();
    ~MainWindow();

public slots:
    void changeRValue(int r);
    void changeGValue(int g);
    void changeBValue(int b);
    void changeHValue(int h);
    void changeSValue(int s);
    void changeVValue(int v);


protected:
    QGraphicsScene scene;
    QGraphicsView graphView;

private:
    Ui::MainWindow *ui;
    QColor currentColor;
    void createConnections();
    void setDefaultValues();
    void updateSliders();
};

#endif // MAINWINDOW_H
