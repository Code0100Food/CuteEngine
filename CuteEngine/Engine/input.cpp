#include "input.h"
#include <iostream>
#include <QKeyEvent>
#include "qt_application.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <myopenglwidget.h>
#include "mainscene.h"
#include "entity.h"
#include "transform.h"

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
    else if(event->key() == Qt::Key_F)
    {
        Entity* target_entity = customApp->main_scene()->GetSelectedEntity();
        if(target_entity != nullptr)
        {
            QVector3D target_pos = target_entity->GetTransform()->GetPosition();
            target_pos-=gl_widget->GetCameraPosition();
            target_pos+= gl_widget->GetCameraFront();

            gl_widget->TranslateCamera(target_pos.x(),target_pos.y(),target_pos.z());
        }
    }
    else if(event->key() == Qt::Key_Alt)
    {
        alt_key = true;
    }
}

void Input::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Alt)
    {
        alt_key = false;
    }
}

void Input::mouseMoveEvent(QMouseEvent *event)
{

    if(mouse_mid)
    {
        if(alt_key)
        {
            std::cout<<"nide"<<std::endl;
            QVector3D target_pos = gl_widget->GetCameraFront();
            gl_widget->RotateCamera((mouse_pos.y() - event->pos().y()) ,(mouse_pos.x() - event->pos().x()) , 0.0f);
            target_pos -= gl_widget->GetCameraFront();
            std::cout<< (mouse_pos.y() - event->pos().y()) <<std::endl;
            std::cout<< target_pos.x() << std::endl;
            std::cout<< target_pos.y() << std::endl;
            std::cout<< target_pos.z() << std::endl;
            gl_widget->TranslateCamera(target_pos.x(),target_pos.y(),target_pos.z());
        }
        else
        {
            gl_widget->TranslateCamera((mouse_pos.x() - event->pos().x()) * drag_scale, -(mouse_pos.y() - event->pos().y()) * drag_scale, 0.0f);
        }
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
