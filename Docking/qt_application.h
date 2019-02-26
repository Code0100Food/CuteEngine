#ifndef QT_APPLICATION_H
#define QT_APPLICATION_H

class MainWindow;
class MainScene;

class qt_Application
{
public:
    qt_Application();
    ~qt_Application();

    void Start();

private:
    MainWindow* window;
    MainScene* scene;
};

#endif // QT_APPLICATION_H
