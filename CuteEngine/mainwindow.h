#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QFileDialog>
#include "qt_application.h"

namespace Ui
{
class MainWindow;
class Rendering;
}

class inspector;
class HierarchyWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:

    void openProject();
    void saveProject();
    void customExit();

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:

    Ui::MainWindow* _uiMain = nullptr;
    Ui::Rendering* _uiRendering = nullptr;
    inspector* _inspector = nullptr;
    HierarchyWidget* _hierarchy = nullptr;

public:

    Ui::MainWindow* uiMain(){return _uiMain;}
    HierarchyWidget* hierarchy(){return _hierarchy;}
};

#endif // MAINWINDOW_H
