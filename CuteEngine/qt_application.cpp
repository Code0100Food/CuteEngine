#include "qt_application.h"
#include "mainwindow.h"
#include "mainscene.h"

qt_Application::qt_Application(int &argc, char** argv): QApplication(argc,argv)
{

}

qt_Application::~qt_Application()
{
    delete window;
    delete scene;
}

void qt_Application::Start()
{
    window = new MainWindow();
    scene = new MainScene();

    window->show();
}
