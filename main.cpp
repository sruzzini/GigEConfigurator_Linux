#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    //Adding comment to check for auto building
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
