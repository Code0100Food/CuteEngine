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

    Ui::MainWindow* _uiMain;
    Ui::Rendering* _uiRendering;
    inspector* _inspector;
};

#endif // MAINWINDOW_H
