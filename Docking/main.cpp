#include "qt_application.h"
#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <QSurfaceFormat>

int main(int argc, char *argv[])
{
    qt_Application app(argc, argv);
    QSurfaceFormat format = QSurfaceFormat::defaultFormat();
    format.setMinorVersion(3);
    format.setMajorVersion(3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setDepthBufferSize(24);
    format.setRedBufferSize(8);
    format.setGreenBufferSize(8);
    format.setBlueBufferSize(8);
    format.setAlphaBufferSize(8);
    format.setSwapBehavior(QSurfaceFormat::SwapBehavior::DoubleBuffer);
    QSurfaceFormat::setDefaultFormat(format);

    app.Start();

    return app.exec();
}
