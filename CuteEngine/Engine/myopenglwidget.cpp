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
#include "deferredrenderer.h"
#include <QOpenGLFramebufferObject>
#include <QImage>

#pragma comment(lib, "OpenGL32.lib")

myopenglwidget::myopenglwidget(QWidget* parent) : QOpenGLWidget(parent)
{
    setMinimumSize(QSize(256,256));
    setMouseTracking(true);


    //Camera is loaded as identity
    camera = new Camera();
    aspect_ratio = ((float)width())/height();
    camera->projection_matrix = QMatrix4x4((1.0f/tan(DEGTORAD(field_of_view)/2))/aspect_ratio, 0, 0, 0, 0, (1.0f/tan( DEGTORAD(field_of_view)/2)), 0 ,0 ,0 ,0, ((far_plane_distance + near_plane_distance)/(near_plane_distance - far_plane_distance)), ((2*near_plane_distance*far_plane_distance)/(near_plane_distance - far_plane_distance)),0,0,-1,0);
    deferred_renderer = new DeferredRenderer();
}

myopenglwidget::~myopenglwidget()
{
    makeCurrent();
    finalizeGL();

    //delete projection;
    delete camera;
}

void myopenglwidget::initializeGL()
{
    initializeOpenGLFunctions();
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);

    makeCurrent();
    deferred_renderer->SetMainBuffer(width(), height());

    std::string path = customApp->applicationDirPath().toStdString();
    std::string vertex_path = path + "/../../CuteEngine/Resources/Shaders/screen_vertex.vert";
    std::string frag_path = path + "/../../CuteEngine/Resources/Shaders/screen_fragment.frag";

    std::cout<<path<<std::endl;

    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_path.c_str());
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, frag_path.c_str());

    program.link();
    program.bind();

    QVector3D vertices[] = {
        QVector3D(-1.0f,-1.0f,0.0f), QVector3D(0.0f,0.0f, 0.0f) ,
        QVector3D(1.0f,1.0f, 0.0f),  QVector3D(1.0f,1.0f, 0.0f),
        QVector3D(-1.0f, 1.0f, 0.0f),QVector3D(0.0f,1.0f, 0.0f),
        QVector3D(-1.0f,-1.0f,0.0f), QVector3D(0.0f,0.0f, 0.0f) ,
        QVector3D(1.0f,-1.0f, 0.0f), QVector3D(1.0f,0.0f, 0.0f),
        QVector3D(1.0f,1.0f, 0.0f),  QVector3D(1.0f,1.0f, 0.0f)
    };

    vbo.create();
    vbo.bind();
    vbo.setUsagePattern(QOpenGLBuffer::UsagePattern::StaticDraw);
    vbo.allocate(vertices,6 * 2 * sizeof(QVector3D));

    vao.create();
    vao.bind();
    const GLint compCount = 3;
    const int strideBytes = sizeof(QVector3D) * 2;
    const int offsetBytes0 = 0;
    const int offsetBytes1 = sizeof(QVector3D);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(0,compCount,GL_FLOAT,GL_FALSE,strideBytes,(void*)(offsetBytes0));
    glVertexAttribPointer(1, compCount,GL_FLOAT,GL_FALSE,strideBytes,(void*)(offsetBytes1));

    vao.release();
    vbo.release();
    program.release();

    connect(context(),SIGNAL(aboutToBeDestroyed()),this,SLOT(finalizeGL()));

    //Debug
    patrick = new Mesh();
    patrick->LoadModel("C:/Users/Th_Sola/Desktop/Patrick/Patrick.obj");
    patrick->Reload();

   deferred_renderer->LoadShaders(customApp->applicationDirPath().toStdString().c_str());

}

void myopenglwidget::resizeGL(int width, int height)
{
    //Update Projection
    aspect_ratio = ((float)width) / height;
    QVector4D first((1.0f/tan(DEGTORAD(field_of_view)/2))/aspect_ratio, 0.0f, 0.0f, 0.0f);
    QVector4D second(0.0f, (1.0f/tan(DEGTORAD(field_of_view)/2)), 0.0f, 0.0f);
    QVector4D third(0.0f, 0.0f, ((far_plane_distance + near_plane_distance)/(near_plane_distance - far_plane_distance)), ((2*near_plane_distance*far_plane_distance)/(near_plane_distance - far_plane_distance)));

    camera->projection_matrix.setRow(0, first);
    camera->projection_matrix.setRow(1, second);
    camera->projection_matrix.setRow(2, third);
}

void myopenglwidget::paintGL()
{
    makeCurrent();

    camera->PrepareMatrices();
    deferred_renderer->Render(camera);

    //Draw Final Scene
    if(program.bind())
    {
        program.setUniformValue(program.uniformLocation("color_texture"), 0);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, deferred_renderer->main_buffer->GetColorTexture());

        vao.bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
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

void myopenglwidget::keyReleaseEvent(QKeyEvent *event)
{
    customApp->input()->keyReleaseEvent(event);
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
    camera->view_matrix.translate(x,y,z);
}

void myopenglwidget::RotateCamera(float x, float y, float z)
{
    camera->view_matrix.rotate(x,y,z);
}

QVector3D myopenglwidget::GetCameraPosition() const
{
    return camera->view_matrix.column(3).toVector3D();
}

QVector3D myopenglwidget::GetCameraFront() const
{
    return camera->view_matrix.column(2).toVector3D();
}
