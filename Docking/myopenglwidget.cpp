#include "myopenglwidget.h"
#include "qt_application.h"
#include <iostream>

#pragma comment(lib, "OpenGL32.lib")

myopenglwidget::myopenglwidget(QWidget* parent) : QOpenGLWidget(parent)
{
    setMinimumSize(QSize(256,256));
}

myopenglwidget::~myopenglwidget()
{
    makeCurrent();
    finalizeGL();
}

void myopenglwidget::initializeGL()
{
    initializeOpenGLFunctions();

    program.create();

    std::string vertex_shader_path = qApp->applicationDirPath().toUtf8();
    std::cout<< vertex_shader_path << std::endl;
    vertex_shader_path += "/../../Docking/Resources/Shaders/shader1_vert.vert.txt";

    std::string fragment_shader_path = qApp->applicationDirPath().toUtf8();
    std::cout<< fragment_shader_path << std::endl;
    fragment_shader_path += "/../../Docking/Resources/Shaders/shader1_frag.frag.txt";

    program.addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_shader_path.c_str());
    program.addShaderFromSourceFile(QOpenGLShader::Fragment, fragment_shader_path.c_str());
    program.link();
    program.bind();

    QVector3D vertices[] = {
        QVector3D(-0.5f,-0.5f,0.0f),QVector3D(1.0f,0.0f,0.0f) ,
        QVector3D(0.5f,-0.5f,0.0f),QVector3D(0.0f,1.0f,0.0f),
        QVector3D(0.0f,0.5f,0.0f), QVector3D(0.0f,0.0f,1.0f)
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
}

void myopenglwidget::resizeGL(int width, int height)
{

}

void myopenglwidget::paintGL()
{
    glClearColor(0.5f,0.7f,0.9f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    if(program.bind())
    {
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
