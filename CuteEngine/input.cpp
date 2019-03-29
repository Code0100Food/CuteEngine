#include "input.h"
#include <iostream>
#include <QKeyEvent>

Input::Input()
{
    this->grabKeyboard();
    this->grabMouse();
}


void Input::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        std::cout<<"key in"<<std::endl;
        //camera->translate(0.0f,0.0f,1.0f);
        //camera->rotate(1.0f,QVector3D(0.0f,1.0f,0.0f));
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
