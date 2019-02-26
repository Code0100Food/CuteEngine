#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>

class qt_Application;

namespace Ui
{
class MainWindow;
class Rendering;
}

class inspector;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:

    void openProject();
    void saveProject();
    void customExit();

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void SetApp(qt_Application& _app);

private:
    qt_Application* app = nullptr;

    Ui::MainWindow* _uiMain;
    Ui::Rendering* _uiRendering;
    inspector* _inspector;
};

#endif // MAINWINDOW_H
