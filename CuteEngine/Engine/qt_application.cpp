#include "qt_application.h"
#include "mainwindow.h"
#include "mainscene.h"
#include "input.h"

qt_Application::qt_Application(int &argc, char** argv): QApplication(argc,argv)
{

}

qt_Application::~qt_Application()
{
    delete _window;
    delete _scene;
    delete _input;
}

void qt_Application::Start()
{
    _window = new MainWindow();
    _scene = new MainScene();
    _input = new Input();

    _window->show();
}
