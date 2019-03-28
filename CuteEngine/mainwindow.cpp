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

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(Update()));
    connect(timer, SIGNAL(timeout()), this, SLOT(update()));
    timer->start(UPDATE_DT);
}

MainWindow::~MainWindow()
{
    delete _uiMain;
    delete _uiRendering;
    delete timer;
    delete _scroll;
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

QWidget *MainWindow::scene_render()
{
    return _uiMain->centralWidget->findChild<QWidget*>("viewport");
}

