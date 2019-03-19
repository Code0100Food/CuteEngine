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
class QVBoxLayout;
class QTimer;

#define UPDATE_DT 16

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:

    void Update();
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
    QTimer* timer = nullptr;

public:

    Ui::MainWindow* uiMain(){return _uiMain;}
    QWidget* scene_render();
    HierarchyWidget* hierarchy(){return _hierarchy;}
    Inspector* inspector() {return _inspector;}

};

#endif // MAINWINDOW_H
