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
#include <qmath.h>

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
    QVector3D displacement_vector;
    if(event->key() == Qt::Key_W)
    {
        displacement_vector += QVector3D(-sinf(qDegreesToRadians(gl_widget->GetCamera()->yaw)) * cosf(qDegreesToRadians(gl_widget->GetCamera()->pitch)),
                                         sinf(qDegreesToRadians(gl_widget->GetCamera()->pitch)),
                                         -cosf(qDegreesToRadians(gl_widget->GetCamera()->yaw)) * cosf(qDegreesToRadians(gl_widget->GetCamera()->pitch)));
        displacement_vector *= UPDATE_DT * wasd_speed;
    }
    else if(event->key() == Qt::Key_S)
    {
        displacement_vector += QVector3D(sinf(qDegreesToRadians(gl_widget->GetCamera()->yaw)) * cosf(qDegreesToRadians(gl_widget->GetCamera()->pitch)),
                                         -sinf(qDegreesToRadians(gl_widget->GetCamera()->pitch)),
                                         cosf(qDegreesToRadians(gl_widget->GetCamera()->yaw)) * cosf(qDegreesToRadians(gl_widget->GetCamera()->pitch)));
        displacement_vector *= UPDATE_DT * wasd_speed;
    }
    else if(event->key() == Qt::Key_A)
    {
        displacement_vector += QVector3D(-cosf(qDegreesToRadians(gl_widget->GetCamera()->yaw)),
                                         0.0f,
                                         sinf(qDegreesToRadians(gl_widget->GetCamera()->yaw)));
        displacement_vector *= UPDATE_DT * wasd_speed;
    }
    //Cos en 0 val 1
    //Sin en 1 val 0
    else if(event->key() == Qt::Key_D)
    {
        displacement_vector += QVector3D(cosf(qDegreesToRadians(gl_widget->GetCamera()->yaw)),
                                         0.0f,
                                         -sinf(qDegreesToRadians(gl_widget->GetCamera()->yaw)));
        displacement_vector *= UPDATE_DT * wasd_speed;
    }
    /*else if(event->key() == Qt::Key_E)
    {
        displacement_vector += QVector3D(0.0f,
                                         cosf(qDegreesToRadians(gl_widget->GetCamera()->pitch)),
                                         sinf(qDegreesToRadians(gl_widget->GetCamera()->pitch)));
        displacement_vector *= UPDATE_DT * wasd_speed;
    }
    else if(event->key() == Qt::Key_Q)
    {
        displacement_vector += QVector3D(sinf(qDegreesToRadians(gl_widget->GetCamera()->yaw)),
                                         -cosf(qDegreesToRadians(gl_widget->GetCamera()->pitch)),
                                         -sinf(qDegreesToRadians(gl_widget->GetCamera()->pitch)));
        displacement_vector *= UPDATE_DT * wasd_speed;
    }*/

    else if(event->key() == Qt::Key_F)
    {
        Entity* target_entity = customApp->main_scene()->GetSelectedEntity();
        if(target_entity != nullptr)
        {
            QVector3D target_pos = target_entity->GetTransform()->GetPosition();
            float yaw_angle = atan2(0.0f,gl_widget->GetCamera()->position.x() -  target_pos.x());
            float pitch_angle = atan2(gl_widget->GetCamera()->position.y() -  target_pos.y(), 0.0f);

            std::cout<<"Target pos"<<std::endl;
            std::cout<<target_pos.x()<<std::endl;
            std::cout<<target_pos.y()<<std::endl;
            std::cout<<target_pos.z()<<std::endl;
            std::cout<<"Camera pos"<<std::endl;
            std::cout<<gl_widget->GetCamera()->position.x()<<std::endl;
            std::cout<<gl_widget->GetCamera()->position.y()<<std::endl;
            std::cout<<gl_widget->GetCamera()->position.z()<<std::endl;
            std::cout<<"Yaw&pitch"<<std::endl;
            std::cout<<yaw_angle<<std::endl;
            std::cout<<pitch_angle<<std::endl;
            gl_widget->GetCamera()->yaw += yaw_angle;
            gl_widget->GetCamera()->pitch += pitch_angle;

            /*
            target_pos-=gl_widget->GetCameraPosition();
            target_pos+= gl_widget->GetCameraFront();

            gl_widget->TranslateCamera(target_pos.x(),target_pos.y(),target_pos.z());*/
        }
    }
    else if(event->key() == Qt::Key_Alt)
    {
        alt_key = true;
    }

    //displacement_vector *= 0.05f;

    gl_widget->GetCamera()->position += displacement_vector;
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
    mouse_prev_x = mouse_x;
    mouse_prev_y = mouse_y;
    mouse_x = event->pos().x();
    mouse_y = event->pos().y();

    int mouse_x_delta = mouse_x - mouse_prev_x;
    int mouse_y_delta = mouse_y - mouse_prev_y;

    float &yaw = gl_widget->GetCamera()->yaw;
    float &pitch = gl_widget->GetCamera()->pitch;

    if(mouse_mid)
    {
        if(alt_key)
        {
            if(mouse_x_delta != 0 || mouse_y_delta != 0)
            {

            yaw -= rotation_speed * mouse_x_delta * UPDATE_DT;
            pitch -= rotation_speed * mouse_y_delta * UPDATE_DT;
            while(yaw < 0.0f)yaw += 360.0f;
            while(yaw > 360.0f)yaw -= 360.0f;
            if(pitch > 89.0f)pitch = 89.0f;
            if(pitch < -89.0f)pitch = -89.0f;
            }
        }
        else
        {
            gl_widget->GetCamera()->position += QVector3D(mouse_x_delta * drag_speed * UPDATE_DT, -mouse_y_delta * drag_speed * UPDATE_DT, 0.0f);
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

    QVector3D displacement_vector;
    if(event->delta() > 0)
    {
        displacement_vector += QVector3D(-sinf(qDegreesToRadians(gl_widget->GetCamera()->yaw)) * cosf(qDegreesToRadians(gl_widget->GetCamera()->pitch)),
                                         sinf(qDegreesToRadians(gl_widget->GetCamera()->pitch)),
                                         -cosf(qDegreesToRadians(gl_widget->GetCamera()->yaw)) * cosf(qDegreesToRadians(gl_widget->GetCamera()->pitch)));
        displacement_vector *= UPDATE_DT * scroll_speed;
    }
    else if(event->delta() < 0)
    {
        displacement_vector += QVector3D(sinf(qDegreesToRadians(gl_widget->GetCamera()->yaw)) * cosf(qDegreesToRadians(gl_widget->GetCamera()->pitch)),
                                         -sinf(qDegreesToRadians(gl_widget->GetCamera()->pitch)),
                                         cosf(qDegreesToRadians(gl_widget->GetCamera()->yaw)) * cosf(qDegreesToRadians(gl_widget->GetCamera()->pitch)));
        displacement_vector *= UPDATE_DT * scroll_speed;
    }

    if(event->delta() != 0)
    {
        gl_widget->GetCamera()->position += displacement_vector;
    }
}

void Input::enterEvent(QEvent* event)
{

}

void Input::leaveEvent(QEvent* event)
{

}
