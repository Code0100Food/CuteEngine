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
    if(right_mouse)
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
        else if(event->key() == Qt::Key_D)
        {
            displacement_vector += QVector3D(cosf(qDegreesToRadians(gl_widget->GetCamera()->yaw)),
                                             0.0f,
                                             -sinf(qDegreesToRadians(gl_widget->GetCamera()->yaw)));
            displacement_vector *= UPDATE_DT * wasd_speed;
        }
        else if(event->key() == Qt::Key_E)
        {
            displacement_vector += QVector3D(-sinf(qDegreesToRadians(gl_widget->GetCamera()->yaw)),
                                             cosf(qDegreesToRadians(gl_widget->GetCamera()->pitch)) ,
                                             cosf(qDegreesToRadians(gl_widget->GetCamera()->yaw)) * sinf(qDegreesToRadians(gl_widget->GetCamera()->pitch)));
            displacement_vector *= UPDATE_DT * wasd_speed;
        }
        else if(event->key() == Qt::Key_Q)
        {
            displacement_vector += QVector3D(sinf(qDegreesToRadians(gl_widget->GetCamera()->yaw)),
                                             -cosf(qDegreesToRadians(gl_widget->GetCamera()->pitch)) ,
                                             -cosf(qDegreesToRadians(gl_widget->GetCamera()->yaw)) * sinf(qDegreesToRadians(gl_widget->GetCamera()->pitch)));
            displacement_vector *= UPDATE_DT * wasd_speed;
        }

        gl_widget->GetCamera()->position += displacement_vector;
    }

    if(event->key() == Qt::Key_F)
    {
        Entity* target_entity = customApp->main_scene()->GetSelectedEntity();
        if(target_entity != nullptr)
        {
            //QVector3D target_pos = target_entity->GetTransform()->GetPosition();
            //&& QVector3D(target_entity->GetTransform()->GetPosition() - gl_widget->GetCamera()->target_position).length() > 0.001f
            float len = QVector3D(gl_widget->GetCamera()->position - gl_widget->GetCamera()->target_position).length();

            gl_widget->GetCamera()->position = target_entity->GetTransform()->GetPosition();
            gl_widget->GetCamera()->target_position = target_entity->GetTransform()->GetPosition();

            QVector3D back_vec = QVector3D(sinf(qDegreesToRadians(gl_widget->GetCamera()->yaw)) * cosf(qDegreesToRadians(gl_widget->GetCamera()->pitch)),
                                                         -sinf(qDegreesToRadians(gl_widget->GetCamera()->pitch)),
                                                         cosf(qDegreesToRadians(gl_widget->GetCamera()->yaw)) * cosf(qDegreesToRadians(gl_widget->GetCamera()->pitch)));

            back_vec *= len;

            gl_widget->GetCamera()->position += back_vec;

            //float yaw_angle = atan2(gl_widget->GetCamera()->position.z() - gl_widget->GetCamera()->target_position.z(), gl_widget->GetCamera()->target_position.x() - gl_widget->GetCamera()->position.x());

            //float pitch_angle = atan2(gl_widget->GetCamera()->position.y() -  gl_widget->GetCamera()->target_position.y(), gl_widget->GetCamera()->position.z() - gl_widget->GetCamera()->target_position.z());

            std::cout<<"Target pos"<<std::endl;
            std::cout<<gl_widget->GetCamera()->target_position.x()<<std::endl;
            std::cout<<gl_widget->GetCamera()->target_position.y()<<std::endl;
            std::cout<<gl_widget->GetCamera()->target_position.z()<<std::endl;

            std::cout<<"Camera pos"<<std::endl;
            std::cout<<gl_widget->GetCamera()->position.x()<<std::endl;
            std::cout<<gl_widget->GetCamera()->position.y()<<std::endl;
            std::cout<<gl_widget->GetCamera()->position.z()<<std::endl;

            std::cout<<"Yaw&pitch"<<std::endl;
            //std::cout<<yaw_angle<<std::endl;
            //std::cout<<pitch_angle<<std::endl;

            //gl_widget->GetCamera()->yaw += yaw_angle;
            //gl_widget->GetCamera()->pitch += pitch_angle;
        }
    }

    if(event->key() == Qt::Key_Alt)
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
    mouse_prev_x = mouse_x;
    mouse_prev_y = mouse_y;
    mouse_x = event->pos().x();
    mouse_y = event->pos().y();

    int mouse_x_delta = mouse_x - mouse_prev_x;
    int mouse_y_delta = mouse_y - mouse_prev_y;

    float &yaw = gl_widget->GetCamera()->yaw;
    float &pitch = gl_widget->GetCamera()->pitch;

    QVector3D displacement_vector;

    if(mouse_mid)
    {
        if(mouse_x_delta < 0)
        {
            //D move
            QVector3D cur_displacement_vector = QVector3D(cosf(qDegreesToRadians(gl_widget->GetCamera()->yaw)),
                                             0.0f,
                                             -sinf(qDegreesToRadians(gl_widget->GetCamera()->yaw)));

            cur_displacement_vector *= UPDATE_DT * drag_speed * abs(mouse_x_delta);
            displacement_vector += cur_displacement_vector;
        }
        else if(mouse_x_delta > 0)
        {
            //A move
            QVector3D cur_displacement_vector = QVector3D(-cosf(qDegreesToRadians(gl_widget->GetCamera()->yaw)),
                                             0.0f,
                                             sinf(qDegreesToRadians(gl_widget->GetCamera()->yaw)));

            cur_displacement_vector *= UPDATE_DT * drag_speed * abs(mouse_x_delta);
            displacement_vector += cur_displacement_vector;
        }
        if(mouse_y_delta < 0)
        {
            //Q move
            QVector3D cur_displacement_vector = QVector3D(sinf(qDegreesToRadians(gl_widget->GetCamera()->yaw)),
                                             -cosf(qDegreesToRadians(gl_widget->GetCamera()->pitch)) ,
                                             -cosf(qDegreesToRadians(gl_widget->GetCamera()->yaw)) * sinf(qDegreesToRadians(gl_widget->GetCamera()->pitch)));

            cur_displacement_vector *= UPDATE_DT * drag_speed * abs(mouse_y_delta);
            displacement_vector += cur_displacement_vector;
        }
        else if(mouse_y_delta > 0)
        {
            //E move
            QVector3D cur_displacement_vector = QVector3D(-sinf(qDegreesToRadians(gl_widget->GetCamera()->yaw)),
                                             cosf(qDegreesToRadians(gl_widget->GetCamera()->pitch)) ,
                                             cosf(qDegreesToRadians(gl_widget->GetCamera()->yaw)) * sinf(qDegreesToRadians(gl_widget->GetCamera()->pitch)));

            cur_displacement_vector *= UPDATE_DT * drag_speed * abs(mouse_y_delta);
            displacement_vector += cur_displacement_vector;
        }
    }

    gl_widget->GetCamera()->position += displacement_vector;

    if(alt_key && left_mouse)
    {
        if(mouse_x_delta != 0 || mouse_y_delta != 0)
        {
            float len = QVector3D(gl_widget->GetCamera()->position - gl_widget->GetCamera()->target_position).length();

            QVector3D front_vec = QVector3D(-sinf(qDegreesToRadians(gl_widget->GetCamera()->yaw)) * cosf(qDegreesToRadians(gl_widget->GetCamera()->pitch)),
                                                         sinf(qDegreesToRadians(gl_widget->GetCamera()->pitch)),
                                                         -cosf(qDegreesToRadians(gl_widget->GetCamera()->yaw)) * cosf(qDegreesToRadians(gl_widget->GetCamera()->pitch)));
            front_vec *= len;

            gl_widget->GetCamera()->position += front_vec;

            yaw -= rotation_speed * mouse_x_delta * UPDATE_DT;
            pitch -= rotation_speed * mouse_y_delta * UPDATE_DT;
            while(yaw < 0.0f)yaw += 360.0f;
            while(yaw > 360.0f)yaw -= 360.0f;
            if(pitch > 89.0f)pitch = 89.0f;
            if(pitch < -89.0f)pitch = -89.0f;

            QVector3D back_vec = QVector3D(sinf(qDegreesToRadians(gl_widget->GetCamera()->yaw)) * cosf(qDegreesToRadians(gl_widget->GetCamera()->pitch)),
                                                         -sinf(qDegreesToRadians(gl_widget->GetCamera()->pitch)),
                                                         cosf(qDegreesToRadians(gl_widget->GetCamera()->yaw)) * cosf(qDegreesToRadians(gl_widget->GetCamera()->pitch)));

            back_vec *= len;

            gl_widget->GetCamera()->position += back_vec;
        }
    }

    mouse_pos = event->pos();
}

void Input::mousePressEvent(QMouseEvent *event)
{
    mouse_pos = event->pos();

    if(event->button() == Qt::MidButton)
    {
        mouse_mid = true;
    }

    if(event->button() == Qt::RightButton)
    {
        right_mouse = true;
    }

    if(event->button() == Qt::LeftButton)
    {
        left_mouse = true;
    }
}

void Input::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::MidButton)
    {
        mouse_mid = false;
    }

    if(event->button() == Qt::RightButton)
    {
        right_mouse = false;
    }

    if(event->button() == Qt::LeftButton)
    {
        left_mouse = false;
    }
}

void Input::wheelEvent(QWheelEvent *event)
{
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
