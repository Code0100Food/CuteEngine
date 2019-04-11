#include "deferredrenderer.h"
#include <QOpenGLFunctions_3_3_Core>
#include "camera.h"

DeferredRenderer::DeferredRenderer()
{

}

bool DeferredRenderer::PassGrid(Camera *camera, std::string path)
{
     //GLenum draw_buffers[] = {GL_COLOR_ATTACHMENT3};
     //glDrawBuffers(1, draw_buffers);

     //OpenGLState glState;
     //glState.depthTest = true;

     std::string grid_vertex_path = path + "/../../CuteEngine/Resources/Shaders/grid_vertex.vert";
     std::string grid_frag_path = path + "/../../CuteEngine/Resources/Shaders/grid_fragment.frag";

     program_grid.create();
     program_grid.addShaderFromSourceFile(QOpenGLShader::Vertex, grid_vertex_path.c_str());
     program_grid.addShaderFromSourceFile(QOpenGLShader::Fragment, grid_frag_path.c_str());

     program_grid.link();
     if (program_grid.bind())
     {
         //QVector4D camera_parameters; // = camera->GetLRBT();
         //program_grid->setUniformValue("left", camera_parameters.x());
         //program_grid->setUniformValue("right", camera_parameters.y());
         //program_grid->setUniformValue("bottom", camera_parameters.z());
         //program_grid->setUniformValue("top", camera_parameters.w());
         //program_grid->setUniformValue("znear", camera->;
         //program_grid->setUniformValue("worldMatrix", camera->a());
         //program_grid->setUniformValue("viewMatrix", camera->a());
         //program_grid->setUniformValue("projectionMatrix", camera->a());
         //
         //resource_manager->quad->submeshes[0]->draw();

         program_grid.release();
     }
    return true;
}

void DeferredRenderer::PassBackground(Camera *camera, std::string path)
{
    GLenum draw_buffers = { GL_COLOR_ATTACHMENT3 };
    glDrawBuffer(draw_buffers);

    //OpenGLState glState;
    //glState.depthTest = true;
    //glState.depthFunc = GL_EQUAL;
    //glState.apply();

    std::string background_vertex_path = path + "/../../CuteEngine/Resources/Shaders/background_vertex.vert";
    std::string background_frag_path = path + "/../../CuteEngine/Resources/Shaders/background_fragment.frag";

    program_background.create();
    program_background.addShaderFromSourceFile(QOpenGLShader::Vertex, background_vertex_path.c_str());
    program_background.addShaderFromSourceFile(QOpenGLShader::Fragment, background_frag_path.c_str());

    program_background.link();
    if (program_background.bind())
    {
        //QVector4D viewport_parameters; // = camera->GetLRBT();
        //program_background->setUniformValue("viewportSize", QVector2D(viewportWidth, viewportHeight);
        //program_background->setUniformValue("left", viewport_parameters.x());
        //program_background->setUniformValue("right", viewport_parameters.y());
        //program_background->setUniformValue("bottom", viewport_parameters.z());
        //program_background->setUniformValue("top", viewport_parameters.w());
        //program_background->setUniformValue("znear", camera->GetZNear();
        //program_background->setUniformValue("worldMatrix", camera->GetWorldMatrix());
        //program_background->setUniformValue("backgroundColor", scene->GetBackgroundColor());
        //
        //resource_manager->quad->submeshes[0]->draw();

        program_background.release();
    }
}
