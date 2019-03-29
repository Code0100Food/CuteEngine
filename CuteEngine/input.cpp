#include "input.h"
#include <iostream>
#include <QKeyEvent>
#include "qt_application.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <myopenglwidget.h>

Input::Input()
{
    this->grabKeyboard();
    this->grabMouse();

    gl_widget = customApp->main_window()->uiMain()->openGLWidget;
}

void Input::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        gl_widget->TranslateCamera(0.0f,0.0f,-1.0f);
    }
    else if(event->key() == Qt::Key_S)
    {
        gl_widget->TranslateCamera(0.0f,0.0f,1.0f);
    }
    else if(event->key() == Qt::Key_A)
    {
        gl_widget->TranslateCamera(-1.0f,0.0f,0.0f);
    }
    else if(event->key() == Qt::Key_D)
    {
        gl_widget->TranslateCamera(1.0f,0.0f,0.0f);
    }
    else if(event->key() == Qt::Key_E)
    {
        gl_widget->TranslateCamera(0.0f,1.0f,0.0f);
    }
    else if(event->key() == Qt::Key_Q)
    {
        gl_widget->TranslateCamera(0.0f,-1.0f,0.0f);
    }
}

void Input::mouseMoveEvent(QMouseEvent *event)
{
    std::cout<<"nide"<<std::endl;
    if(event->button() == Qt::MidButton)
    {
        //char* buffer;
         //itoa(event->key(),buffer,10);
         std::cout<<"nide"<<std::endl;
    }
}

void Input::mousePressEvent(QMouseEvent *event)
{
    //std::cout<<"nide"<<std::endl;
    if(event->button() == Qt::MidButton)
    {
        std::cout<<"nide"<<std::endl;
    }
}
