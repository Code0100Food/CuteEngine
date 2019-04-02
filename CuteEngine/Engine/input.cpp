#include "input.h"
#include <iostream>
#include <QKeyEvent>
#include "qt_application.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <myopenglwidget.h>

Input::Input()
{
    gl_widget = customApp->main_window()->uiMain()->openGLWidget;
}

Input::~Input()
{
    gl_widget = nullptr;
}

void Input::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        gl_widget->TranslateCamera(0.0f,0.0f,-key_move_scale);
    }
    else if(event->key() == Qt::Key_S)
    {
        gl_widget->TranslateCamera(0.0f,0.0f,key_move_scale);
    }
    else if(event->key() == Qt::Key_A)
    {
        gl_widget->TranslateCamera(-key_move_scale,0.0f,0.0f);
    }
    else if(event->key() == Qt::Key_D)
    {
        gl_widget->TranslateCamera(key_move_scale,0.0f,0.0f);
    }
    else if(event->key() == Qt::Key_E)
    {
        gl_widget->TranslateCamera(0.0f,-key_move_scale,0.0f);
    }
    else if(event->key() == Qt::Key_Q)
    {
        gl_widget->TranslateCamera(0.0f,key_move_scale,0.0f);
    }
}

void Input::mouseMoveEvent(QMouseEvent *event)
{
    std::cout<<"nide"<<std::endl;
    if(mouse_mid)
    {
        gl_widget->TranslateCamera((mouse_pos.x() - event->pos().x()) * drag_scale, -(mouse_pos.y() - event->pos().y()) * drag_scale, 0.0f);
    }

    mouse_pos = event->pos();
}

void Input::mousePressEvent(QMouseEvent *event)
{
    mouse_pos = event->pos();

    if(event->button() == Qt::MidButton)
    {
        std::cout<<"on"<<std::endl;
        mouse_mid = true;
    }
}

void Input::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MidButton)
    {
        std::cout<<"off"<<std::endl;
        mouse_mid = false;
    }
}

void Input::wheelEvent(QWheelEvent *event)
{
    std::cout<<"dasdadaon"<<std::endl;

    if(event->delta() != 0)
    {
        gl_widget->TranslateCamera(0.0f, 0.0f, event->delta() * scroll_scale);
    }
}

void Input::enterEvent(QEvent* event)
{

}

void Input::leaveEvent(QEvent* event)
{

}
