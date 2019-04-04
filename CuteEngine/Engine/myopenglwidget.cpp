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
#include <QOpenGLFramebufferObject>

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

    glGenTextures(1, &colorTexture);
    glBindTexture(GL_TEXTURE_2D, colorTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width(), height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glGenTextures(1, &depthTexture);
    glBindTexture(GL_TEXTURE_2D, depthTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width(), height(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    glGenFramebuffers(1, &fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, colorTexture, 0);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
    glDrawBuffer(GL_COLOR_ATTACHMENT0);

    GLenum status = glCheckFramebufferStatus(GL_FRAMEBUFFER);
     switch(status)
     {
        case GL_FRAMEBUFFER_COMPLETE: // OK
            std::cout<< "OK!" << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT:
            std::cout<< "Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_ATTACHMENT" << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT:
            std::cout<< "Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_MISSING_ATTACHMENT" << std::endl;
             break;
        case GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER:
            std::cout<< "Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_DRAW_BUFFER" << std::endl;
            break;
        case GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER:
            std::cout<< "Framebuffer ERROR: GL_FRAMEBUFFER_INCOMPLETE_READ_BUFFER" << std::endl;
            break;
        case GL_FRAMEBUFFER_UNSUPPORTED:
            std::cout<< "Framebuffer ERROR: GL_FRAMEBUFFER_UNSUPPORTED" << std::endl;
            break;
        default:
            std::cout<< "Framebuffer ERROR: Unknown ERROR" << std::endl;
            break;
     }


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

    // FrameBuffer Object has a void texture atm
    // glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    // GLenum buffs[] =
    //  { GL_COLOR_ATTACHMENT0 };
    // glDrawBuffers(1, buffs);

    glClearDepth(1.0);
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

    // FrameBuffer Object has a void texture atm
    // QOpenGLFramebufferObject::bindDefault();
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
    camera->translate(x,y,z);
}

void myopenglwidget::RotateCamera(float x, float y, float z)
{
    camera->rotate(x,y,z);
}

QVector3D myopenglwidget::GetCameraPosition() const
{
    return camera->column(3).toVector3D();
}

QVector3D myopenglwidget::GetCameraFront() const
{
    return camera->column(2).toVector3D();
}
