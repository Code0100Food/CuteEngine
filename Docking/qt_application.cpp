#include "qt_application.h"
#include "mainwindow.h"
#include "mainscene.h"

qt_Application::qt_Application()
{
    window = new MainWindow();
    scene = new MainScene();
}

qt_Application::~qt_Application()
{
    delete window;
    delete scene;
}

void qt_Application::Start()
{
    window->show();
}
