#include "qt_application.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    qt_Application app(argc, argv);
    app.Start();


    return app.exec();
}
