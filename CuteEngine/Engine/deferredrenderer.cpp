#include "qt_application.h"
#include "mainscene.h"
#include "deferredrenderer.h"
#include <QOpenGLFunctions_3_3_Core>
#include "camera.h"
#include "entity.h"
#include "transform.h"
#include <QOpenGLFunctions>
#include "mainwindow.h"
#include "myopenglwidget.h"
#include "resourcemanager.h"
#include "../Data/mesh.h"
#include "light.h"
#include "environment.h"
#include "../Data/texture.h"
#include "../Data/hdr_texture.h"
#include "../Data/submesh.h"


#include "qopenglextrafunctions.h"

///////////////////////////////////////FRAME BUFFER OBJECT////////////////////////////////////
FrameBufferObject::FrameBufferObject(int width, int height, bool has_depth_texture)
{
    Create(width, height);
}

FrameBufferObject::~FrameBufferObject()
{
    this->Destroy();
}

void FrameBufferObject::Resize(int width, int height)
{
    Destroy();
    Create(width, height);
}

void FrameBufferObject::Create(int width, int height)
{
    viewport_width = width;
    viewport_height = height;

    QOpenGLExtraFunctions* gl_functions = QOpenGLContext::currentContext()->extraFunctions();

    glGenTextures(1, &color_texture);
    glBindTexture(GL_TEXTURE_2D, color_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glGenTextures(1, &normals_texture);
    glBindTexture(GL_TEXTURE_2D, normals_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);

    glGenTextures(1, &shaded_color);
    glBindTexture(GL_TEXTURE_2D, shaded_color);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);

    glGenTextures(1, &selection_texture);
    glBindTexture(GL_TEXTURE_2D, selection_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, nullptr);

    glGenTextures(1, &depth_texture);
    glBindTexture(GL_TEXTURE_2D, depth_texture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, nullptr);

    gl_functions->glGenFramebuffers(1, &frame_buffer);
    gl_functions->glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
    gl_functions->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_texture, 0);
    gl_functions->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, normals_texture, 0);
    gl_functions->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT2, GL_TEXTURE_2D, shaded_color, 0);
    gl_functions->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT3, GL_TEXTURE_2D, selection_texture, 0);
    gl_functions->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depth_texture, 0);

    GLenum buffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 , GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3};
    gl_functions->glDrawBuffers(4, buffers);

    GLenum status = gl_functions->glCheckFramebufferStatus(GL_FRAMEBUFFER);
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

    QOpenGLFramebufferObject::bindDefault();
}

void FrameBufferObject::Destroy()
{
    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();
    gl_functions->glDeleteTextures(1, &color_texture);

    gl_functions->glDeleteTextures(1, &normals_texture);

    gl_functions->glDeleteTextures(1, &shaded_color);

    gl_functions->glDeleteTextures(1,&selection_texture);

    if(depth_texture != 0)
        gl_functions->glDeleteTextures(1, &depth_texture);

    //gl_functions->glDeleteBuffers(1, &frame_buffer);
}

void FrameBufferObject::Bind()
{
    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();
    gl_functions->glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
}

void FrameBufferObject::UnBind()
{
    QOpenGLFramebufferObject::bindDefault();
}

SingleFrameBufferObject::SingleFrameBufferObject()
{

}

SingleFrameBufferObject::~SingleFrameBufferObject()
{
    this->Destroy();
}

void SingleFrameBufferObject::Bind()
{
    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();
    gl_functions->glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
}

void SingleFrameBufferObject::UnBind()
{
    QOpenGLFramebufferObject::bindDefault();
}

void SingleFrameBufferObject::Set(unsigned int id, unsigned int level)
{
    color_texture = id;
    level_mipmap = level;

    QOpenGLExtraFunctions* gl_functions = QOpenGLContext::currentContext()->extraFunctions();

    gl_functions->glGenFramebuffers(1, &frame_buffer);
    gl_functions->glBindFramebuffer(GL_FRAMEBUFFER, frame_buffer);
    gl_functions->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, color_texture, level_mipmap);

    GLenum buffers[] = {GL_COLOR_ATTACHMENT0};
    gl_functions->glDrawBuffers(1, buffers);

    GLenum status = gl_functions->glCheckFramebufferStatus(GL_FRAMEBUFFER);
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

            QOpenGLFramebufferObject::bindDefault();
}

void SingleFrameBufferObject::Destroy()
{
    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();
    gl_functions->glDeleteTextures(1, &color_texture);
}

////////////////////////////////////////DEFERRED RENDERER/////////////////////////////////////

DeferredRenderer::DeferredRenderer()
{
    glGenTextures(1, &CubeMapId);
    glBindTexture(GL_TEXTURE_CUBE_MAP, CubeMapId);

    for(unsigned int i = 0; i < 6; i++)
    {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, resolution, resolution, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
    }

    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

bool DeferredRenderer::PassGrid(Camera *camera)
{

    if(customApp->main_scene()->IsGridPrint() == false)
    {
        return true;
    }

     GLenum draw_buffers = GL_COLOR_ATTACHMENT2;
     glDrawBuffer(draw_buffers);

     glEnable(GL_BLEND);
     glEnable(GL_DEPTH_TEST);
     glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

     if (program_grid.bind())
     {
         QVector4D camera_parameters = camera->GetLeftRightBottomTop();
         program_grid.setUniformValue("left", camera_parameters.x());
         program_grid.setUniformValue("right", camera_parameters.y());
         program_grid.setUniformValue("bottom", camera_parameters.z());
         program_grid.setUniformValue("top", camera_parameters.w());
         program_grid.setUniformValue("z_near", camera->z_near);
         program_grid.setUniformValue("z_far", camera->z_far);
         program_grid.setUniformValue("worldMatrix", camera->world_matrix);
         program_grid.setUniformValue("viewMatrix", camera->view_matrix);
         program_grid.setUniformValue("projectionMatrix", camera->projection_matrix);

        customApp->main_window()->resource_manager()->ScreenQuad()->Draw();

         program_grid.release();
     }

     glDisable(GL_BLEND);
    return true;
}

void DeferredRenderer::PassBackground(Camera *camera)
{
    GLenum draw_buffers = GL_COLOR_ATTACHMENT2;
    glDrawBuffer(draw_buffers);

    if (program_background.bind())
    {
        QVector4D viewport_parameters = camera->GetLeftRightBottomTop();
        program_background.setUniformValue("viewportSize", QVector2D(main_buffer->GetViewportWidth(), main_buffer->GetViewportHeight()));
        program_background.setUniformValue("left", viewport_parameters.x());
        program_background.setUniformValue("right", viewport_parameters.y());
        program_background.setUniformValue("bottom", viewport_parameters.z());
        program_background.setUniformValue("top", viewport_parameters.w());
        program_background.setUniformValue("znear", camera->z_near);
        program_background.setUniformValue("worldMatrix", camera->world_matrix);
        program_background.setUniformValue("backgroundColor", customApp->main_scene()->GetBackgroundColor());

        customApp->main_window()->resource_manager()->ScreenQuad()->Draw();

        program_background.release();
    }


}

void DeferredRenderer::Render(Camera *camera)
{
    if(!main_buffer) return;

    main_buffer->Bind();

    QOpenGLExtraFunctions* gl_functions = QOpenGLContext::currentContext()->extraFunctions();
    GLenum buffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT2, GL_COLOR_ATTACHMENT3 }; //Albedo, Normals
    gl_functions->glDrawBuffers(4, buffers);

    glEnable(GL_DEPTH_TEST);
    glClearDepth(1.0);
    glClearColor(0.01f,0.01f,0.01f,0.01f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glDrawBuffer(0);


    PassMeshes(camera);

    PassLights(camera);
    PassSkybox(camera);
    ProcessSelection();

    PassGrid(camera);

    //PassBackground(camera);

    if(print_bloom)
        PassBloom();

    main_buffer->UnBind();
}

void DeferredRenderer::Resize(int width, int height)
{
    main_buffer->Resize(width, height);

    DestroyBloomBuffers();
    InitializeBloomBuffers(width,height);
}

void DeferredRenderer::SetMainBuffer(int width, int height)
{
    main_buffer = new FrameBufferObject(width, height, true);
}

void DeferredRenderer::PassMeshes(Camera *camera)
{
    QOpenGLExtraFunctions* gl_functions = QOpenGLContext::currentContext()->extraFunctions();
    GLenum buffers[] = {GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1, GL_COLOR_ATTACHMENT3 }; //Albedo, Normals
    gl_functions->glDrawBuffers(3, buffers);

    if(standard_program.bind())
    {
        standard_program.setUniformValue(standard_program.uniformLocation("projection_matrix"), camera->projection_matrix);
        standard_program.setUniformValue(standard_program.uniformLocation("view_matrix"), camera->view_matrix);

        foreach(Entity* entity, customApp->main_scene()->GetEntities())
        {
            standard_program.setUniformValue(standard_program.uniformLocation("model_matrix"), (*entity->GetTransform()->GetLocalTransform()));
            standard_program.setUniformValue(standard_program.uniformLocation("is_selected"), entity->is_selected);

            entity->Draw();
        }

        standard_program.release();
    }

}

void DeferredRenderer::PassLights(Camera *camera)
{
    QOpenGLExtraFunctions* gl_functions = QOpenGLContext::currentContext()->extraFunctions();
    GLenum buffers =  GL_COLOR_ATTACHMENT2 ; //Shaded
    glDrawBuffer(buffers);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    glDepthMask(GL_FALSE);

    if(program_lights.bind())
    {
        //Textures to shader
        program_lights.setUniformValue(program_lights.uniformLocation("color_texture"), 0);
        gl_functions->glActiveTexture(GL_TEXTURE0); //Color
        gl_functions->glBindTexture(GL_TEXTURE_2D, main_buffer->GetColorTexture());

        program_lights.setUniformValue(program_lights.uniformLocation("normal_texture"), 1);
        gl_functions->glActiveTexture(GL_TEXTURE1); //Normals
        glBindTexture(GL_TEXTURE_2D, main_buffer->GetNormalTexture());

        program_lights.setUniformValue(program_lights.uniformLocation("depth_texture"), 2);
        gl_functions->glActiveTexture(GL_TEXTURE2); //Depth
        glBindTexture(GL_TEXTURE_2D, main_buffer->GetDepthTexture());

        //Variables to shadfer
        program_lights.setUniformValue(program_lights.uniformLocation("camera_position"), camera->position);
        program_lights.setUniformValue(program_lights.uniformLocation("projection_matrix_transposed"), camera->projection_matrix.inverted());
        program_lights.setUniformValue(program_lights.uniformLocation("view_matrix_transposed"), camera->view_matrix.inverted());
        program_lights.setUniformValue(program_lights.uniformLocation("viewport_width"), main_buffer->GetViewportWidth());
        program_lights.setUniformValue(program_lights.uniformLocation("viewport_height"), main_buffer->GetViewportHeight());
        program_lights.setUniformValue(program_lights.uniformLocation("near"), camera->z_near);
        program_lights.setUniformValue(program_lights.uniformLocation("far"), camera->z_far);

        foreach(Entity* light, customApp->main_scene()->GetLights())
        {
            Light* light_component = (Light*)light->FindComponent(COMPONENT_LIGHT);

            program_lights.setUniformValue(program_lights.uniformLocation("light_type"), light_component->GetType());
            program_lights.setUniformValue(program_lights.uniformLocation("light_color"), light_component->GetColor());
            program_lights.setUniformValue(program_lights.uniformLocation("light_intensity"), light_component->GetIntensity());
            program_lights.setUniformValue(program_lights.uniformLocation("light_direction"), light->GetTransform()->GetLocalTransform()->column(2).toVector3D());
            customApp->main_window()->resource_manager()->ScreenQuad()->Draw();
        }

        glDisable(GL_BLEND);
        glDepthMask(GL_TRUE);
        //std::cout << "LOL" << std::endl;
        program_lights.release();
    }
}

void DeferredRenderer::PassSkybox(Camera* camera)
{

    QOpenGLExtraFunctions* gl_functions = QOpenGLContext::currentContext()->extraFunctions();
    GLenum draw_buffers = GL_COLOR_ATTACHMENT2;
    glDrawBuffer(draw_buffers);

    glDisable(GL_CULL_FACE);

    QMatrix4x4 model;
    model.translate(0.0f, 15.0f, -15.0f);

    if(program_draw_skybox.bind())
    {
        program_draw_skybox.setUniformValue(program_draw_skybox.uniformLocation("Cubemap"), 0);
        gl_functions->glActiveTexture(GL_TEXTURE0);
        gl_functions->glBindTexture(GL_TEXTURE_CUBE_MAP, customApp->main_window()->environment()->GetSkyboxTexture());

        program_draw_skybox.setUniformValue(program_draw_skybox.uniformLocation("projection_matrix"), camera->projection_matrix);
        program_draw_skybox.setUniformValue(program_draw_skybox.uniformLocation("view_matrix"), camera->view_matrix);
        program_draw_skybox.setUniformValue(program_draw_skybox.uniformLocation("camera_pos"), camera->position);
        program_draw_skybox.setUniformValue(program_draw_skybox.uniformLocation("model_matrix"), model);


        customApp->main_window()->resource_manager()->SkyboxQuad()->Draw();

        program_draw_skybox.release();
    }

    glEnable(GL_CULL_FACE);

   /* if(!customApp->main_window()->environment()->SkyBoxReady())
        return;

    QOpenGLExtraFunctions* gl_functions = QOpenGLContext::currentContext()->extraFunctions();
    GLenum draw_buffers = GL_COLOR_ATTACHMENT0;
    glDrawBuffer(draw_buffers);


    glDepthMask(GL_FALSE);
    glDisable(GL_CULL_FACE);


    if(program_draw_skybox.bind())
    {
        program_draw_skybox.setUniformValue(program_draw_skybox.uniformLocation("Cubemap"), 0);
        gl_functions->glActiveTexture(GL_TEXTURE0);
        gl_functions->glBindTexture(GL_TEXTURE_CUBE_MAP, customApp->main_window()->environment()->GetSkyboxTexture());

        program_draw_skybox.setUniformValue(program_draw_skybox.uniformLocation("projection_matrix"), camera->projection_matrix);
        program_draw_skybox.setUniformValue(program_draw_skybox.uniformLocation("view_matrix"), camera->view_matrix);
        program_draw_skybox.setUniformValue(program_draw_skybox.uniformLocation("camera_pos"), camera->position);
        customApp->main_window()->resource_manager()->SkyboxQuad()->Draw();

        program_draw_skybox.release();
    }
   glEnable(GL_CULL_FACE);
   glDepthMask(GL_TRUE);*/

    /*QOpenGLExtraFunctions* gl_functions = QOpenGLContext::currentContext()->extraFunctions();

    GLuint captureFBO;
    gl_functions->glGenFramebuffers(1, &captureFBO);

    gl_functions->glDisable(GL_CULL_FACE);

    if(program_skybox.bind())
    {
        program_skybox.setUniformValue("equirectangular_map", 0);
        program_skybox.setUniformValue("projection_matrix", camera->projection_matrix);

        gl_functions->glActiveTexture(GL_TEXTURE0);
        gl_functions->glBindTexture(GL_TEXTURE_2D, customApp->main_window()->environment()->texture->GetIndex());

        //gl_functions->glViewport(0, 0, customApp->main_window()->environment()->environment_map->resoultion,
        //                         customApp->main_window()->environment()->environment_map->resoultion);GLTextureCube
        gl_functions->glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);

        //QMatrix4x4 captureViews[] =
        //{
        //   QVector4D(1, 0, 0, 1),
        //
        //   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        //   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        //   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
        //   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
        //   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
        //   glm::lookAt(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3( 0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
        //};

        for(unsigned int i = 0; i < 6; ++i)
        {
            //program_skybox.setUniformValue("view_matrix", captureViews[i]);
            gl_functions->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                                                 customApp->main_window()->environment()->texture->GetIndex(), 0);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
            customApp->main_window()->resource_manager()->SkyboxQuad()->Draw();
        }
    }

    gl_functions->glBindTexture(GL_TEXTURE_CUBE_MAP, customApp->main_window()->environment()->texture->GetIndex());
    gl_functions->glGenerateMipmap(GL_TEXTURE_CUBE_MAP);


    program_skybox.release();*/
}

void DeferredRenderer::ProcessSelection()
{

    QOpenGLExtraFunctions* gl_functions = QOpenGLContext::currentContext()->extraFunctions();
    GLenum draw_buffers = GL_COLOR_ATTACHMENT2;
    glDrawBuffer(draw_buffers);

    glDisable(GL_DEPTH_TEST);

    if (program_selection.bind())
    {
        //std::cout<<main_buffer->GetSelectionTexture()<<std::endl;

        gl_functions->glActiveTexture(GL_TEXTURE0);
        gl_functions->glBindTexture(GL_TEXTURE_2D, main_buffer->GetSelectionTexture());
        program_selection.setUniformValue(program_selection.uniformLocation("mask"), 0);
        //program_selection.setUniformValue(program_selection.uniformLocation("mask"));

        customApp->main_window()->resource_manager()->ScreenQuad()->Draw();
        //std::cout<<"hol2a1"<<std::endl;
        program_selection.release();
    }

   glEnable(GL_DEPTH_TEST);
}

void DeferredRenderer::PassBloom()
{
    GetBrightestPixels();

    PassBlur(true);
    PassBlur(false);

    PassBlur(true);
    PassBlur(false);

    PassBlur(true);
    PassBlur(false);

    ProcessBloom();
}

void DeferredRenderer::GetBrightestPixels()
{
    QOpenGLExtraFunctions* gl_functions = QOpenGLContext::currentContext()->extraFunctions();
    main_buffer->UnBind();

    bloom_buffers_a[0].Bind();

    if(bright_pixels_program.bind())
    {
        gl_functions->glActiveTexture(GL_TEXTURE0);
        gl_functions->glBindTexture(GL_TEXTURE_2D,main_buffer->GetShadedTexture());
        bright_pixels_program.setUniformValue(bright_pixels_program.uniformLocation("get_bright_pixels_texture"),0);

        customApp->main_window()->resource_manager()->ScreenQuad()->Draw();

        bright_pixels_program.release();
    }

    bloom_buffers_a[0].UnBind();

    gl_functions->glBindTexture(GL_TEXTURE_2D, bloom_buffers_a[0].color_texture);
    gl_functions->glGenerateMipmap(GL_TEXTURE_2D);
}

void DeferredRenderer::PassBlur(bool vertical)
{
    QOpenGLExtraFunctions* gl_functions = QOpenGLContext::currentContext()->extraFunctions();

    for(int i = 0; i < 5; i++)
    {
         vertical ? bloom_buffers_b[i].Bind() : bloom_buffers_a[i].Bind();
         if(blur_program.bind())
         {
                 gl_functions->glActiveTexture(GL_TEXTURE0);
                 gl_functions->glBindTexture(GL_TEXTURE_2D, vertical ? bloom_buffers_a[0].color_texture : bloom_buffers_b[0].color_texture);
                 blur_program.setUniformValue(program_selection.uniformLocation("bright_pixels_texture"), 0);

                 blur_program.setUniformValue(blur_program.uniformLocation("mipmap_level"), i);
                 blur_program.setUniformValue(blur_program.uniformLocation("is_vertical_blur"), vertical);

                 customApp->main_window()->resource_manager()->ScreenQuad()->Draw();


             blur_program.release();
         }
         vertical ? bloom_buffers_b[i].UnBind() : bloom_buffers_a[i].UnBind();
    }

}

void DeferredRenderer::ProcessBloom()
{
    main_buffer->Bind();

    QOpenGLExtraFunctions* gl_functions = QOpenGLContext::currentContext()->extraFunctions();
    GLenum draw_buffers = GL_COLOR_ATTACHMENT2;
    glDrawBuffer(draw_buffers);

    glEnable(GL_BLEND);
    glBlendFunc(GL_ONE, GL_ONE);
    glDepthMask(GL_FALSE);

    if(bloom_program.bind())
    {
        gl_functions->glActiveTexture(GL_TEXTURE0);
        gl_functions->glBindTexture(GL_TEXTURE_2D, bloom_buffers_a[0].color_texture);
        blur_program.setUniformValue(bloom_program.uniformLocation("blurred_texture"), 0);
        blur_program.setUniformValue(bloom_program.uniformLocation("mipmap_number"), 5);

        customApp->main_window()->resource_manager()->ScreenQuad()->Draw();

        bloom_program.release();
    }

    glDisable(GL_BLEND);
    glDepthMask(GL_TRUE);
}

void DeferredRenderer::LoadShaders(const char *char_path)
{
    LoadStandardShader(char_path);
    LoadGridShader(char_path);
    LoadBackgroundShader(char_path);
    LoadLightsShader(char_path);
    LoadSelectionShader(char_path);
    LoadMaskShader(char_path);
    LoadSkybox(char_path);
    LoadBrightPixelsShader(char_path);
    LoadBlurShader(char_path);
    LoadBloomShader(char_path);
    LoadDrawSkybox(char_path);
}

void DeferredRenderer::LoadStandardShader(const char* char_path)
{
    std::string vertex_path = char_path;
    vertex_path += "/../../CuteEngine/Resources/Shaders/standard_vertex.vert";

    std::string frag_path = char_path;
    frag_path += "/../../CuteEngine/Resources/Shaders/standard_fragment.frag";

    standard_program.create();
    standard_program.addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_path.c_str());
    standard_program.addShaderFromSourceFile(QOpenGLShader::Fragment, frag_path.c_str());

    standard_program.link();
}

void DeferredRenderer::InitializeBloomBuffers(int width, int height)
{
    QOpenGLExtraFunctions* gl_functions = QOpenGLContext::currentContext()->extraFunctions();

    glGenTextures(1, &bloom_texture_a);
    glBindTexture(GL_TEXTURE_2D, bloom_texture_a);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
    gl_functions->glGenerateMipmap(GL_TEXTURE_2D);

    glGenTextures(1, &bloom_texture_b);
    glBindTexture(GL_TEXTURE_2D, bloom_texture_b);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 4);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, width, height, 0, GL_RGBA, GL_FLOAT, nullptr);
    gl_functions->glGenerateMipmap(GL_TEXTURE_2D);

    for(int k = 0; k < 5; k++)
    {
        bloom_buffers_a[k].Set(bloom_texture_a,k);
        bloom_buffers_b[k].Set(bloom_texture_b,k);
    }
}

void DeferredRenderer::DestroyBloomBuffers()
{
    for(int k = 0; k < 5; k++)
    {
        bloom_buffers_a[k].Destroy();
        bloom_buffers_b[k].Destroy();
    }
}

void DeferredRenderer::LoadGridShader(const char* char_path)
{
    std::string vertex_path = char_path;
    vertex_path += "/../../CuteEngine/Resources/Shaders/grid_vertex.vert";

    std::string frag_path = char_path;
    frag_path += "/../../CuteEngine/Resources/Shaders/grid_fragment.frag";

    if(program_grid.isLinked())
    {
    program_grid.removeAllShaders();
    }

    program_grid.create();
    program_grid.addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_path.c_str());
    program_grid.addShaderFromSourceFile(QOpenGLShader::Fragment, frag_path.c_str());

    program_grid.link();
}

void DeferredRenderer::LoadBackgroundShader(const char* char_path)
{
    std::string vertex_path = char_path;
    vertex_path += "/../../CuteEngine/Resources/Shaders/background_vertex.vert";

    std::string frag_path = char_path;
    frag_path += "/../../CuteEngine/Resources/Shaders/background_fragment.frag";

    program_background.create();
    program_background.addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_path.c_str());
    program_background.addShaderFromSourceFile(QOpenGLShader::Fragment, frag_path.c_str());

    program_background.link();
}

void DeferredRenderer::LoadLightsShader(const char *char_path)
{
    std::string vertex_path = char_path;
    vertex_path += "/../../CuteEngine/Resources/Shaders/IluminationVertex.vert";

    std::string frag_path = char_path;
    frag_path += "/../../CuteEngine/Resources/Shaders/IluminationFragment.frag";

    program_lights.create();
    program_lights.addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_path.c_str());
    program_lights.addShaderFromSourceFile(QOpenGLShader::Fragment, frag_path.c_str());

    program_lights.link();
}

void DeferredRenderer::LoadSelectionShader(const char *char_path)
{
    std::string vertex_path = char_path;
    vertex_path += "/../../CuteEngine/Resources/Shaders/selection_vertex.vert";

    std::string frag_path = char_path;
    frag_path += "/../../CuteEngine/Resources/Shaders/selection_fragment.frag";

    program_selection.create();
    program_selection.addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_path.c_str());
    program_selection.addShaderFromSourceFile(QOpenGLShader::Fragment, frag_path.c_str());

    program_selection.link();
}

void DeferredRenderer::LoadMaskShader(const char *char_path)
{
    std::string vertex_path = char_path;
    vertex_path += "/../../CuteEngine/Resources/Shaders/mask_vertex.vert";

    std::string frag_path = char_path;
    frag_path += "/../../CuteEngine/Resources/Shaders/mask_fragment.frag";

    program_mask.create();
    program_mask.addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_path.c_str());
    program_mask.addShaderFromSourceFile(QOpenGLShader::Fragment, frag_path.c_str());

    program_mask.link();
}

void DeferredRenderer::LoadSkybox(const char *char_path)
{
    std::string vertex_path = char_path;
    vertex_path += "/../../CuteEngine/Resources/Shaders/skybox_vertex.vert";

    std::string frag_path = char_path;
    frag_path += "/../../CuteEngine/Resources/Shaders/skybox_fragment.frag";

    program_skybox.create();
    program_skybox.addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_path.c_str());
    program_skybox.addShaderFromSourceFile(QOpenGLShader::Fragment, frag_path.c_str());

    program_skybox.link();
}

void DeferredRenderer::LoadDrawSkybox(const char *char_path)
{
    std::string vertex_path = char_path;
    vertex_path += "/../../CuteEngine/Resources/Shaders/skybox_draw_vertex.vert";

    std::string frag_path = char_path;
    frag_path += "/../../CuteEngine/Resources/Shaders/skybox_draw_fragment.frag";

    program_draw_skybox.create();
    program_draw_skybox.addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_path.c_str());
    program_draw_skybox.addShaderFromSourceFile(QOpenGLShader::Fragment, frag_path.c_str());

    program_draw_skybox.link();
}

void DeferredRenderer::LoadBrightPixelsShader(const char *char_path)
{
    std::string vertex_path = char_path;
    vertex_path += "/../../CuteEngine/Resources/Shaders/bright_pixels_vertex.vert";

    std::string frag_path = char_path;
    frag_path += "/../../CuteEngine/Resources/Shaders/bright_pixels_fragment.frag";

    bright_pixels_program.create();
    bright_pixels_program.addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_path.c_str());
    bright_pixels_program.addShaderFromSourceFile(QOpenGLShader::Fragment, frag_path.c_str());

    bright_pixels_program.link();
}

void DeferredRenderer::LoadBlurShader(const char *char_path)
{
    std::string vertex_path = char_path;
    vertex_path += "/../../CuteEngine/Resources/Shaders/blur_vertex.vert";

    std::string frag_path = char_path;
    frag_path += "/../../CuteEngine/Resources/Shaders/blur_fragment.frag";

    blur_program.create();
    blur_program.addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_path.c_str());
    blur_program.addShaderFromSourceFile(QOpenGLShader::Fragment, frag_path.c_str());

    blur_program.link();
}

void DeferredRenderer::LoadBloomShader(const char *char_path)
{
    std::string vertex_path = char_path;
    vertex_path += "/../../CuteEngine/Resources/Shaders/bloom_vertex.vert";

    std::string frag_path = char_path;
    frag_path += "/../../CuteEngine/Resources/Shaders/bloom_fragment.frag";

    bloom_program.create();
    bloom_program.addShaderFromSourceFile(QOpenGLShader::Vertex, vertex_path.c_str());
    bloom_program.addShaderFromSourceFile(QOpenGLShader::Fragment, frag_path.c_str());

    bloom_program.link();
}

bool DeferredRenderer::BakeHDRTexture(hdr_texture* texture_to_bake)
{
    QOpenGLExtraFunctions* gl_functions = QOpenGLContext::currentContext()->extraFunctions();

    if(customApp->main_window()->resource_manager()->SkyboxQuad()->NeedsReload())
        return false;

    //Framebuffer to draw cubemap texture
    unsigned int capture_frame_buffer = 0;
    gl_functions->glGenFramebuffers(1, &capture_frame_buffer);

    std::cout<< "BAKE: " << capture_frame_buffer << std::endl;

    //Projection Matrixs
    QMatrix4x4 projection;
    projection.setToIdentity();
    projection.perspective(90.0f, 1.0f, 0.1f, 150.0f);

    //View Matrixs, one for each face of the cube
    QMatrix4x4 view_matrix_cubemap;
    QMatrix4x4 view_matrix_cubemap1;
    QMatrix4x4 view_matrix_cubemap2;
    QMatrix4x4 view_matrix_cubemap3;
    QMatrix4x4 view_matrix_cubemap4;
    QMatrix4x4 view_matrix_cubemap5;


    QMatrix4x4 view_matrices[6];

    view_matrix_cubemap.lookAt(QVector3D(1.0f, 0.0f, 0.0f), QVector3D(0.0f, 0.0f, 0.0f),  QVector3D(0.0f, 1.0f, 0.0f));
    view_matrices[0] = (view_matrix_cubemap);

    view_matrix_cubemap1.lookAt(QVector3D(-1.0f, 0.0f, 0.0f), QVector3D(0.0f, 0.0f, 0.0f),  QVector3D(0.0f, 1.0f, 0.0f));
    view_matrices[1] = (view_matrix_cubemap1);

    view_matrix_cubemap2.lookAt(QVector3D(0.0f, 1.0f, 0.0f), QVector3D(0.0f, 0.0f, 0.0f),  QVector3D(0.0f, 0.0f, -1.0f));
    view_matrices[2] = (view_matrix_cubemap2);

    view_matrix_cubemap3.lookAt(QVector3D(0.0f, -1.0f, 0.0f), QVector3D(0.0f, 0.0f, 0.0f),  QVector3D(0.0f, 0.0f, 1.0f));
    view_matrices[3] = (view_matrix_cubemap3);

    view_matrix_cubemap4.lookAt(QVector3D(0.0f, 0.0f, 1.0f), QVector3D(0.0f, 0.0f, 0.0f),  QVector3D(0.0f, 1.0f, 0.0f));
    view_matrices[4] = (view_matrix_cubemap4);

    view_matrix_cubemap5.lookAt(QVector3D(0.0f, 0.0f, -1.0f), QVector3D(0.0f, 0.0f, 0.0f),  QVector3D(0.0f, 1.0f, 0.0f));
    view_matrices[5] = (view_matrix_cubemap5);


    glDisable(GL_CULL_FACE);
    glDepthMask(GL_FALSE);

    if(program_skybox.bind())
    {

        program_skybox.setUniformValue(program_skybox.uniformLocation("equirectangular_map"), 0);
        gl_functions->glActiveTexture(GL_TEXTURE0);
        gl_functions->glBindTexture(GL_TEXTURE_2D, texture_to_bake->GetHDRTexture());

        gl_functions->glViewport(0, 0, texture_to_bake->GetCubeMapSize(), texture_to_bake->GetCubeMapSize());
        gl_functions->glBindFramebuffer(GL_FRAMEBUFFER, capture_frame_buffer);

        program_skybox.setUniformValue(program_skybox.uniformLocation("projection_matrix"), projection);

        for(unsigned int i = 0; i < 6; i++)
        {
            program_skybox.setUniformValue(program_skybox.uniformLocation("view_matrix"), view_matrices[i]);

            std::cout<<  "CUBEMAP ID: " << texture_to_bake->GetCubeMapexture() << std::endl;

            gl_functions->glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, texture_to_bake->GetCubeMapexture(), 0);
            gl_functions->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            customApp->main_window()->resource_manager()->SkyboxQuad()->meshes[2]->Draw();
        }

        program_skybox.release();
    }

    glDepthMask(GL_TRUE);
    glEnable(GL_CULL_FACE);
    return true;
}
