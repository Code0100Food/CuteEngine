#include "mainwindow.h"
#include "mainscene.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    MainScene s;

    return a.exec();
}
