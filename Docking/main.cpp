#include "qt_application.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qt_Application app;
    app.Start();


    return a.exec();
}
