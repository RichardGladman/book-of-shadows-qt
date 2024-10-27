#include "mainwindow.h"

#include <QApplication>

int version_major = 0;
int version_minor = 3;
int version_patch = 0;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
