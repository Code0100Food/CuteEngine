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
class QScrollArea;
class ResourceManager;
class Environment;

#define UPDATE_DT 16

class MainWindow : public QMainWindow
{
    Q_OBJECT

public slots:

    void Update();
    void openProject();
    void saveProject();
    void customExit();
    void takeScreenshot();

public:

    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void AddWidgetToRender(QWidget* form);

    void dragEnterEvent(QDragEnterEvent *e) override;
    void dropEvent(QDropEvent* drop_event) override;

private:

    Ui::MainWindow* _uiMain = nullptr;
    Ui::Rendering* _uiRendering = nullptr;

    HierarchyWidget* _hierarchy = nullptr;
    Inspector* _inspector = nullptr;
    QScrollArea* _scroll = nullptr;
    QTimer* timer = nullptr;
    ResourceManager* _resource_manager = nullptr;
    Environment* _environment = nullptr;

public:

    Ui::MainWindow* uiMain(){return _uiMain;}
    QWidget* scene_render();
    HierarchyWidget* hierarchy(){return _hierarchy;}
    Inspector* inspector() {return _inspector;}
    ResourceManager* resource_manager() { return _resource_manager; }
    Environment* environment() {return _environment;}
};

#endif // MAINWINDOW_H
