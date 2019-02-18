#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_rendering.h"
#include "inspector.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _uiMain(new Ui::MainWindow),
    _uiRendering(new Ui::Rendering)
{
    _uiMain->setupUi(this);

    //Al tab position on top of the docking area
    setTabPosition(Qt::AllDockWidgetAreas,QTabWidget::TabPosition::North);

    //Create the rendering widget
    QWidget * renderingWidget = new QWidget();
    _uiRendering->setupUi(renderingWidget);
    renderingWidget->show();
    //Set the rendering widget to the rendering tab
    _uiMain->Rendering->setWidget(renderingWidget);

    //Create the inspector widget and add it to the inspector tab
    _inspector = new inspector();
    _uiMain->Inspector->setWidget(_inspector);
    _uiMain->Inspector->setMinimumSize(250,300);
    _uiMain->Inspector->setMaximumSize(300,300);
    QMainWindow::tabifyDockWidget(_uiMain->Inspector, _uiMain->Rendering);

    QDockWidget *dockWidget = new QDockWidget;
    dockWidget->setWindowTitle("Lighting");
    this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, dockWidget);
    tabifyDockWidget(_uiMain->Rendering,dockWidget);

}

MainWindow::~MainWindow()
{
    delete _uiMain;
    delete _uiRendering;
}
