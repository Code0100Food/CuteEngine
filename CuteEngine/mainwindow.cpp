#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "inspector.h"
#include "hierarchywidget.h"
#include "QLayout"
#include <iostream>
#include <QTimer>
#include "mainscene.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _uiMain(new Ui::MainWindow)
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
    _inspector = new Inspector();
    _uiMain->Inspector->setWidget(_inspector);
    _uiMain->Inspector->setMinimumSize(250,300);
    _uiMain->Inspector->setMaximumSize(300,300);

    //Set Hierarchy
    _hierarchy = new HierarchyWidget();
    _uiMain->Hierarchy->setWidget(_hierarchy);

    //_uiMain->Scene_Render->sizePolicy().setHorizontalPolicy(QSizePolicy::);

    //Conect action signals to slots
    connect(_uiMain->actionOpen_Project,SIGNAL(triggered()),this,SLOT(openProject()));
    connect(_uiMain->actionSave_Project,SIGNAL(triggered()),this,SLOT(saveProject()));
    connect(_uiMain->actionExit,SIGNAL(triggered()),this,SLOT(customExit()));

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
    timer->start(UPDATE_DT);
}

MainWindow::~MainWindow()
{
    delete _uiMain;
    delete _uiRendering;
    delete timer;
}

void MainWindow::Update()
{
    customApp->main_scene()->Update();
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

void MainWindow::AddWidgetToRender(QWidget* form)
{
    _uiMain->Scene_Render->findChild<QVBoxLayout*>("verticalLayout")->addWidget(form);   //layout()->addWidget(form);
}

QWidget *MainWindow::scene_render()
{
    return _uiMain->Scene_Render->findChild<QWidget*>("dockWidgetContents_7");
}

