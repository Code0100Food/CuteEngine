#include <QOpenGLFunctions>
#include <QGLWidget>
#include "hdr_texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../Widgets/stb_image.h"

hdr_texture::hdr_texture(const char* image_path) : Resource (RESOURCE_TYPE::RESOURCE_HDR_TEXTURE)
{
    filename = image_path;
    SetReload(true);
}

void hdr_texture::Reload()
{
    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();

    int w = 0;
    int h = 0;
    int comp = 0;
    //if(stbi_is_hdr(filename))
    //{
    //    stbi_set_flip_vertically_on_load(true);
    //    hdr_data = stbi_loadf(filename, &w, &h, &comp, 0);
    //}

    gl_functions->glGenTextures(1, &id);
    gl_functions->glBindTexture(GL_TEXTURE_2D, id);
    gl_functions->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, w, h, 0, GL_RGB, GL_FLOAT, hdr_data);
    gl_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    gl_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    gl_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    gl_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SetReload(false);
}

void hdr_texture::Draw()
{

}

void hdr_texture::Destroy()
{
    if(hdr_data != nullptr)
    {
        stbi_image_free(hdr_data);
        hdr_data = nullptr;
    }
}
