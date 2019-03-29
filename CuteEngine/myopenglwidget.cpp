#include "myopenglwidget.h"
#include <iostream>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QTimer>
#include "qt_application.h"

#pragma comment(lib, "OpenGL32.lib")

myopenglwidget::myopenglwidget(QWidget* parent) : QOpenGLWidget(parent)
{
    setMinimumSize(QSize(256,256));
    this->grabKeyboard();

    //Camera is loaded as identity
    camera = new QMatrix4x4();
}

myopenglwidget::~myopenglwidget()
{
    makeCurrent();
    finalizeGL();
}

void myopenglwidget::initializeGL()
{
    initializeOpenGLFunctions();

    std::string path = customApp->applicationDirPath().toStdString();
    std::string vertex_path = path + "/../../CuteEngine/Resources/Shaders/standard_vertex.vert";
    std::string frag_path = path + "/../../CuteEngine/Resources/Shaders/standard_fragment.frag";

    std::cout<<path<<std::endl;

    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_path.c_str());
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, frag_path.c_str());

    program.link();
    program.bind();

    QVector3D vertices[] = {
        QVector3D(-0.5f,-0.5f,-21.0f),QVector3D(1.0f,0.0f,0.0f) ,
        QVector3D(0.5f,-0.5f, -21.0f),QVector3D(0.0f,1.0f,0.0f),
        QVector3D(0.0f,2.5f,  -21.0f), QVector3D(0.0f,0.0f,1.0f)
    };

    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(vertices,6 * sizeof(QVector3D));

    vao.create();
    vao.bind();
    const GLint compCount = 3;
    const int strideBytes = 2 * sizeof(QVector3D);
    const int offsetBytes0 = 0;
    const int offsetBytes1 = sizeof(QVector3D);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0,compCount,GL_FLOAT,GL_FALSE,strideBytes,(void*)(offsetBytes0));
    glVertexAttribPointer(1,compCount,GL_FLOAT,GL_FALSE,strideBytes,(void*)(offsetBytes1));

    vao.release();
    vbo.release();
    program.release();

    connect(context(),SIGNAL(aboutToBeDestroyed()),this,SLOT(finalizeGL()));

    if(program.bind())
    {
    std::cout<< program.programId()  <<std::endl;

    std::cout<< program.uniformLocation("model_matrix")<<std::endl;
    std::cout<<program.uniformLocation("projection_matrix")<<std::endl;
    std::cout<<program.uniformLocation("view_matrix")<<std::endl;

    program.release();
    }

}

void myopenglwidget::resizeGL(int width, int height)
{

}

void myopenglwidget::paintGL()
{
    glClearColor(0.4f,0.4f,0.4f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);    

    QMatrix4x4 lol;

    if(program.bind())
    {
        QMatrix4x4* tmp = new QMatrix4x4(1.0f/(4.0f/3.0f), 0, 0, 0, 0, 1, 0 ,0 ,0 ,0, ((far_plane_distance + near_plane_distance)/(near_plane_distance - far_plane_distance)), ((2*near_plane_distance*far_plane_distance)/(near_plane_distance - far_plane_distance)),0,0,-1,0);

       program.setUniformValue(program.uniformLocation("projection_matrix"), *tmp);
       program.setUniformValue(program.uniformLocation("view_matrix"), *camera);
       program.setUniformValue(program.uniformLocation("model_matrix"), lol);

        vao.bind();
        glDrawArrays(GL_TRIANGLES,0,3);
        vao.release();
        program.release();
    }

}

void myopenglwidget::finalizeGL()
{
    std::cout<<"finalizeGL()" <<std::endl;
}

void myopenglwidget::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_W)
    {
        camera->translate(0.0f,0.0f,1.0f);
    }

    std::cout<<"key pressed"<<std::endl;
}
