#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ui_rendering.h"
#include "inspector.h"
#include "hierarchywidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _uiMain(new Ui::MainWindow),
    _uiRendering(new Ui::Rendering)
{
    //_uiMain->setupUi(this);
    //
    //Al tab position on top of the docking area
    //setTabPosition(Qt::AllDockWidgetAreas,QTabWidget::TabPosition::North);

    //Create the rendering widget
    //QWidget * renderingWidget = new QWidget();
    //_uiRendering->setupUi(renderingWidget);
    //renderingWidget->show();
    //Set the rendering widget to the rendering tab
    //_uiMain->Rendering->setWidget(renderingWidget);

    //Create the inspector widget and add it to the inspector tab
    //_inspector = new inspector();
    //_uiMain->Inspector->setWidget(_inspector);
    //_uiMain->Inspector->setMinimumSize(250,300);
    //_uiMain->Inspector->setMaximumSize(300,300);
    //QMainWindow::tabifyDockWidget(_uiMain->Inspector, _uiMain->Rendering);

    //QDockWidget *dockWidget = new QDockWidget;
    //dockWidget->setWindowTitle("Lighting");
    //this->addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, dockWidget);
    //tabifyDockWidget(_uiMain->Rendering,dockWidget);

    //--------------------------------------HERE STARTS THE ASSIGNMENT---------------------------------------------
    _uiMain->setupUi(this);

    //Al tab position on top of the docking area
    setTabPosition(Qt::AllDockWidgetAreas,QTabWidget::TabPosition::North);

    //Set Inspector
    _inspector = new inspector();
    _uiMain->Inspector->setWidget(_inspector);
    _uiMain->Inspector->setMinimumSize(250,300);
    _uiMain->Inspector->setMaximumSize(300,300);

    //Set Hierarchy
    HierarchyWidget* hierarchy = new HierarchyWidget();
    _uiMain->Hierarchy->setWidget(hierarchy);

    //Conect action signals to slots
    connect(_uiMain->actionOpen_Project,SIGNAL(triggered()),this,SLOT(openProject()));
    connect(_uiMain->actionSave_Project,SIGNAL(triggered()),this,SLOT(saveProject()));
    connect(_uiMain->actionExit,SIGNAL(triggered()),this,SLOT(customExit()));
}

MainWindow::~MainWindow()
{
    delete _uiMain;
    delete _uiRendering;
}

void MainWindow::openProject()
{
    std::printf("Open project");
    QString path = QFileDialog::getOpenFileName(this,"Open Project");
    if(!path.isEmpty())
    {
        //printf(path.toStdString());
    }
}

void MainWindow::saveProject()
{
    std::printf("Save project");
}

void MainWindow::customExit()
{
    //Exit message box
    QMessageBox::StandardButton exit_button = QMessageBox::question(this,"Exit Application","Do you want to exit the application widouth saving the project?");
    if(exit_button == QMessageBox::Yes)
    {
        printf("Exit");
        qApp->quit();
    }
    else
    {
        printf("No exit");
    }
}

