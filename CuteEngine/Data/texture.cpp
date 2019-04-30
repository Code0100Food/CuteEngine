#include "texture.h"
#include <QOpenGLFunctions>

Texture::Texture(unsigned char* buffer, int _width, int _height) : Resource (RESOURCE_TYPE::RESOURCE_TEXTURE)
{
    width = _width;
    height = _height;
    image_data = new unsigned char[_width * _height];
    memcpy(image_data, buffer, _width * _height);

    SetReload(true);
}

Texture::~Texture()
{

}

void Texture::Reload()
{
    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();

    gl_functions->glGenTextures(1, &id);
    gl_functions->glBindTexture(GL_TEXTURE_2D, id);

    gl_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gl_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gl_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    gl_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    gl_functions->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

    SetReload(false);
}

void Texture::Draw()
{

}

void Texture::Destroy()
{

}
