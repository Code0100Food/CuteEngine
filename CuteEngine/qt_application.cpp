#include "qt_application.h"
#include "mainwindow.h"
#include "mainscene.h"

qt_Application::qt_Application(int &argc, char** argv): QApplication(argc,argv)
{

}

qt_Application::~qt_Application()
{
    delete _window;
    delete _scene;
}

void qt_Application::Start()
{
    _window = new MainWindow();
    _scene = new MainScene();

    _window->show();
}
