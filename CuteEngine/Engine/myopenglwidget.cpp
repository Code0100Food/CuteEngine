#include "myopenglwidget.h"
#include <iostream>
#include <QKeyEvent>
#include <QMatrix4x4>
#include <QTimer>
#include "qt_application.h"
#include "math.h"
#include "input.h"
#include "mainscene.h"
#include "entity.h"
#include "../Data/mesh.h"

#pragma comment(lib, "OpenGL32.lib")

myopenglwidget::myopenglwidget(QWidget* parent) : QOpenGLWidget(parent)
{
    setMinimumSize(QSize(256,256));

    //Camera is loaded as identity
    camera = new QMatrix4x4(1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1);
    aspect_ratio = ((float)width())/height();
    projection = new QMatrix4x4((1.0f/tan(DEGTORAD(field_of_view)/2))/aspect_ratio, 0, 0, 0, 0, (1.0f/tan( DEGTORAD(field_of_view)/2)), 0 ,0 ,0 ,0, ((far_plane_distance + near_plane_distance)/(near_plane_distance - far_plane_distance)), ((2*near_plane_distance*far_plane_distance)/(near_plane_distance - far_plane_distance)),0,0,-1,0);
}

myopenglwidget::~myopenglwidget()
{
    makeCurrent();
    finalizeGL();

    delete projection;
    delete camera;
}

void myopenglwidget::initializeGL()
{
   //glEnable(GL_CULL_FACE);

    initializeOpenGLFunctions();
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

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
        QVector3D(-0.5f,-0.5f,-1.0f),QVector3D(1.0f,0.0f,0.0f) ,
        QVector3D(0.5f,-0.5f, -1.0f),QVector3D(0.0f,1.0f,0.0f),
        QVector3D(0.0f,2.5f, -1.0f), QVector3D(0.0f,0.0f,1.0f)
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


    //Debug
    patrick = new Mesh();
    patrick->LoadModel("C:/Users/Th_Sola/Desktop/Patrick/Patrick.obj");
    patrick->Reload();

}

void myopenglwidget::resizeGL(int width, int height)
{
    //Update Projection
    aspect_ratio = ((float)width) / height;
    QVector4D first((1.0f/tan(DEGTORAD(field_of_view)/2))/aspect_ratio, 0.0f, 0.0f, 0.0f);
    QVector4D second(0.0f, (1.0f/tan(DEGTORAD(field_of_view)/2)), 0.0f, 0.0f);
    QVector4D third(0.0f, 0.0f, ((far_plane_distance + near_plane_distance)/(near_plane_distance - far_plane_distance)), ((2*near_plane_distance*far_plane_distance)/(near_plane_distance - far_plane_distance)));

    projection->setRow(0, first);
    projection->setRow(1, second);
    projection->setRow(2, third);
}

void myopenglwidget::paintGL()
{
    makeCurrent();
    glClearColor(0.4f,0.4f,0.4f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    QMatrix4x4 lol;

    if(program.bind())
    {
       program.setUniformValue(program.uniformLocation("projection_matrix"), *projection);
       program.setUniformValue(program.uniformLocation("view_matrix"), camera->inverted());
       program.setUniformValue(program.uniformLocation("model_matrix"), lol);

       patrick->Draw();

       vao.bind();
       glDrawArrays(GL_TRIANGLES, 0, 3);
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
    customApp->input()->keyPressEvent(event);
}

void myopenglwidget::mouseMoveEvent(QMouseEvent* event)
{
    customApp->input()->mouseMoveEvent(event);
}

void myopenglwidget::mousePressEvent(QMouseEvent* event)
{
    customApp->input()->mousePressEvent(event);
    setFocus();
}

void myopenglwidget::mouseReleaseEvent(QMouseEvent* event)
{
    customApp->input()->mouseReleaseEvent(event);
}

void myopenglwidget::wheelEvent(QWheelEvent* event)
{
    customApp->input()->wheelEvent(event);
}

void myopenglwidget::enterEvent(QEvent* event)
{
    customApp->input()->enterEvent(event);
    this->grabKeyboard();
}

void myopenglwidget::leaveEvent(QEvent* event)
{
    customApp->input()->leaveEvent(event);
    this->releaseKeyboard();
}

void myopenglwidget::TranslateCamera(float x, float y, float z)
{
    std::cout<<"nide"<<std::endl;
    camera->translate(x,y,z);
}
