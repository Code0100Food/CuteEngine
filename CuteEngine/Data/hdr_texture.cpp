#include <QOpenGLFunctions>
#include <QGLWidget>
#include "hdr_texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "../Widgets/stb_image.h"
#include "deferredrenderer.h"
#include "qt_application.h"
#include "mainwindow.h"
#include "myopenglwidget.h"

hdr_texture::hdr_texture(const char* image_path) : Resource (RESOURCE_TYPE::RESOURCE_HDR_TEXTURE)
{
    filename = image_path;
    SetReload(true);
}

void hdr_texture::Reload()
{
    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();

    //Load HDR Image
    if(hdr_data == nullptr)
    {
        int comp = 0;
        if(stbi_is_hdr(filename.c_str()))
        {
            stbi_set_flip_vertically_on_load(true);
            hdr_data = stbi_loadf(filename.c_str(), &width, &height, &comp, 0);
        }

        gl_functions->glGenTextures(1, &hdr_id);
        gl_functions->glBindTexture(GL_TEXTURE_2D, hdr_id);
        gl_functions->glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGB, GL_FLOAT, hdr_data);
        gl_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        gl_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        gl_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        gl_functions->glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        std::cout<< "HDRI: " << hdr_id  << "WIDTH: " << width << "HEIGHT: " << height << std::endl;

        //Load Cubemap
        gl_functions->glGenTextures(1, &cubemap_id);
        gl_functions->glBindTexture(GL_TEXTURE_CUBE_MAP, cubemap_id);

        for(unsigned int i = 0; i < 6; i++)
        {
            gl_functions->glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB16F, (width/4), (width/4), 0, GL_RGB, GL_FLOAT, nullptr);
        }
        gl_functions->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        gl_functions->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        gl_functions->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
        gl_functions->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        gl_functions->glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        std::cout<< "CUBEMAP ID: "<< cubemap_id << std::endl;

    }
    if(customApp->main_window()->openglwidget()->GetDeferred()->BakeHDRTexture(this))
    {
        SetReload(false);
    }

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
