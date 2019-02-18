#include "myopenglwidget.h"

#pragma comment(lib, "OpenGL32.lib")

myopenglwidget::myopenglwidget(QWidget* parent) : QOpenGLWidget(parent)
{

}


void myopenglwidget::initializeGL()
{

}

void myopenglwidget::resizeGL(int width, int height)
{

}

void myopenglwidget::paintGL()
{
    glClearColor(0.5f,0.7f,0.9f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}
