#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QImage>
#include <QLabel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private slots:

    void on_transferButton_clicked();

    void on_loadButton_clicked();

private:
    Ui::MainWindow *ui;
    QImage *currentFirstImage;
    QImage *currentSecondImage;
    void setImageOnLabel(QImage *img, QLabel *label);
};

#endif // MAINWINDOW_H
