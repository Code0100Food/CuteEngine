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

class Inspector;
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

    void AddWidgetToRender(QWidget* form);
private:

    Ui::MainWindow* _uiMain = nullptr;
    Ui::Rendering* _uiRendering = nullptr;

    HierarchyWidget* _hierarchy = nullptr;
    Inspector* _inspector = nullptr;

public:

    Ui::MainWindow* uiMain(){return _uiMain;}
    HierarchyWidget* hierarchy(){return _hierarchy;}
    Inspector* inspector() {return _inspector;}

};

#endif // MAINWINDOW_H
