#include "mainwindow.h"
#include <QApplication>

extern MainWindow* mainwindow;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    mainwindow = new MainWindow();
    qDebug() << &mainwindow;
    mainwindow->show();

    return a.exec();
}
