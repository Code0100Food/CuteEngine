#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inspector.h"
#include "hierarchywidget.h"
#include "QLayout"
#include <iostream>
#include <QTimer>
#include "mainscene.h"
#include <QScrollArea>
#include <QDesktopServices>
#include <QDragEnterEvent>
#include <QMimeData>
#include <QUrl>
#include <resourcemanager.h>
#include <environment.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _uiMain(new Ui::MainWindow)
{
    _uiMain->setupUi(this);

    //Al tab position on top of the docking area
    setTabPosition(Qt::AllDockWidgetAreas,QTabWidget::TabPosition::North);

    //Set Inspector
    _scroll = new QScrollArea();

    _inspector = new Inspector();

    _scroll->setWidget(_inspector);
    _scroll->setWidgetResizable(true);

    _uiMain->Inspector->setWidget(_scroll);
    _uiMain->Inspector->setMinimumSize(350,300);
    _uiMain->Inspector->setMaximumSize(350,300);

    //Set Hierarchy
    _hierarchy = new HierarchyWidget();
    _uiMain->Hierarchy->setWidget(_hierarchy);

    //Conect action signals to slots
    connect(_uiMain->actionOpen_Project,SIGNAL(triggered()),this,SLOT(openProject()));
    connect(_uiMain->actionSave_Project,SIGNAL(triggered()),this,SLOT(saveProject()));
    connect(_uiMain->actionExit,SIGNAL(triggered()),this,SLOT(customExit()));
    connect(_uiMain->actionScreenshot,SIGNAL(triggered()),this,SLOT(takeScreenshot()));

    connect(_uiMain->actionAlbedo_Color, SIGNAL(triggered()), _uiMain->openGLWidget, SLOT(ChangeRenderModeColor()));
    connect(_uiMain->actionNormals, SIGNAL(triggered()), _uiMain->openGLWidget, SLOT(ChangeRenderModeNormals()));
    connect(_uiMain->actionDepth, SIGNAL(triggered()), _uiMain->openGLWidget, SLOT(ChangeRenderModeDepth()));
    connect(_uiMain->actionShaded_Color, SIGNAL(triggered()), _uiMain->openGLWidget, SLOT(ChangeRenderModeShaded()));
    connect(_uiMain->actionSelection, SIGNAL(triggered()), _uiMain->openGLWidget, SLOT(ChangeRenderModeSelection()));
    connect(_uiMain->actionBloom_Blur, SIGNAL(triggered()), _uiMain->openGLWidget, SLOT(ChangeRenderModeBloomBlur()));

    //Set Resource Manager
    QDockWidget* resource_dock = new QDockWidget();
    resource_dock->setWindowTitle("Resources");
    _resource_manager = new ResourceManager();
    resource_dock->setWidget(_resource_manager);
    addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, resource_dock);
    tabifyDockWidget(_uiMain->Hierarchy, resource_dock);

    //Set Environment Dock
    QDockWidget* environment_dock = new QDockWidget();
    environment_dock->setWindowTitle("Environment");
    _environment = new Environment();
    //environment_dock->setWidget(_environment);
    //addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea, environment_dock);
    //tabifyDockWidget(_uiMain->Hierarchy, environment_dock);

    //Connect Menu bar
    //_uiMain->menuBar->

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(UPDATE_DT);

    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    delete _uiMain;
    delete _uiRendering;
    delete timer;
    delete _scroll;
    delete _resource_manager;
}

void MainWindow::Update()
{
    customApp->main_scene()->Update();
    _resource_manager->UpdateResources();
    _uiMain->openGLWidget->update();
}

void MainWindow::openProject()
{
    std::printf("Open project");
    QString path = QFileDialog::getOpenFileName(this,"Open Project");
    if(!path.isEmpty())
    {
        QDesktopServices::openUrl(QUrl("file:///"+path,QUrl::TolerantMode));
        //Temp code
        qApp->quit();
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

void MainWindow::takeScreenshot()
{
    //TODO
    //makeCurrent();
    //return grabFrameBuffer();
}

QWidget *MainWindow::scene_render()
{
    return _uiMain->centralWidget->findChild<QWidget*>("viewport");
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    event->accept();
}

void MainWindow::dropEvent(QDropEvent *drop_event)
{

    foreach(const QUrl &path, drop_event->mimeData()->urls())
    {
       std::string file_name = path.toString().toStdString();
       std::cout<< file_name.substr(8) << std::endl;

       resource_manager()->Import(file_name.substr(8));

    }
    //std::cout<< "dropped something" <<std::endl;
}

myopenglwidget* MainWindow::openglwidget()
{
    return _uiMain->openGLWidget;
}
