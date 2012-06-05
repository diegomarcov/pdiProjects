#include <QtGui/QApplication>
#include "mainwindow.h"


int main(int argc, char *argv[])
{
    //initialize application
    QApplication a(argc, argv);
    //setup main window
    MainWindow w;
    w.show();

    return a.exec();
}
