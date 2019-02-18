#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:

    Ui::MainWindow* _uiMain;
    Ui::Rendering* _uiRendering;
    inspector* _inspector;
};

#endif // MAINWINDOW_H
