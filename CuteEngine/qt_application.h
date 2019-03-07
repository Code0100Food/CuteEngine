#ifndef QT_APPLICATION_H
#define QT_APPLICATION_H

#define customApp dynamic_cast<qt_Application*>qApp

#include <QApplication>

class MainWindow;
class MainScene;

class qt_Application: public QApplication
{
public:

    qt_Application(int &argc, char** argv);
    ~qt_Application();

    void Start();

    MainScene* main_scene() {return _scene; }
    MainWindow* main_window() {return _window; }

private:

    MainWindow* _window = nullptr;
    MainScene* _scene = nullptr;
};

#endif // QT_APPLICATION_H
