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
#include "mainwindow.h"
#include "resourcemanager.h"

#pragma comment(lib, "OpenGL32.lib")

myopenglwidget::myopenglwidget(QWidget* parent) : QOpenGLWidget(parent)
{
    setMinimumSize(QSize(256,256));
    setMouseTracking(true);


    //Camera is loaded as identity
    camera = new Camera(width(), height());
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
    deferred_renderer->LoadShaders(customApp->applicationDirPath().toStdString().c_str());

    std::string path = customApp->applicationDirPath().toStdString();
    std::string vertex_path = path + "/../../CuteEngine/Resources/Shaders/screen_vertex.vert";
    std::string frag_path = path + "/../../CuteEngine/Resources/Shaders/screen_fragment.frag";

    program.create();
    program.addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_path.c_str());
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, frag_path.c_str());

    program.link();

    connect(context(),SIGNAL(aboutToBeDestroyed()),this,SLOT(finalizeGL()));
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

    camera->viewport_width = width;
    camera->viewport_height = height;

    deferred_renderer->Resize(width, height);
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

        switch (render_mode)
        {
            case ALBEDO_COLOR:
                glBindTexture(GL_TEXTURE_2D, deferred_renderer->main_buffer->GetColorTexture());
                break;

            case NORMALS:
                glBindTexture(GL_TEXTURE_2D, deferred_renderer->main_buffer->GetNormalTexture());
                break;

            case DEPTH:
                glBindTexture(GL_TEXTURE_2D, deferred_renderer->main_buffer->GetDepthTexture());
                break;

            case FINAL_COLOR:
                glBindTexture(GL_TEXTURE_2D, deferred_renderer->main_buffer->GetShadedTexture());
                break;
        }


        customApp->main_window()->resource_manager()->ScreenQuad()->Draw();

        program.release();
    }
}

void myopenglwidget::finalizeGL()
{
    std::cout<<"finalizeGL()" <<std::endl;
}

void myopenglwidget::ChangeRenderModeColor()
{
    render_mode = RENDERMODE::ALBEDO_COLOR;
}

void myopenglwidget::ChangeRenderModeNormals()
{
    render_mode = RENDERMODE::NORMALS;
}

void myopenglwidget::ChangeRenderModeDepth()
{
    render_mode = RENDERMODE::DEPTH;
}

void myopenglwidget::ChangeRenderModeShaded()
{
    std::cout << "Render Shaded" << std::endl;
    render_mode = RENDERMODE::FINAL_COLOR;
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
