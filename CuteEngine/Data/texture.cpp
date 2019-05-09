#include "texture.h"
#include <QOpenGLFunctions>
#include <QImage>
#include <iostream>
#include <QGLWidget>

Texture::Texture(const char* image_path, TEXTURE_TYPE text_type) : Resource (RESOURCE_TYPE::RESOURCE_TEXTURE)
{
    texture_path = image_path;
    texture_type = text_type;

    SetReload(true);
}

Texture::~Texture()
{

}

void Texture::Reload()
{
    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();

    QImage loader(texture_path.c_str());
    QImage image_able_for_OpenGL = QGLWidget::convertToGLFormat(loader);

    std::cout<< "LOading Texture: "<< GetName()<< std::endl;
    gl_functions->glGenTextures(1, &id);
    gl_functions->glBindTexture(GL_TEXTURE_2D, id);

    gl_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gl_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gl_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_REPEAT);
    gl_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    gl_functions->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, image_able_for_OpenGL.width(), image_able_for_OpenGL.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, image_able_for_OpenGL.bits());

    SetReload(false);
}

void Texture::Draw()
{

}

void Texture::Destroy()
{

}
