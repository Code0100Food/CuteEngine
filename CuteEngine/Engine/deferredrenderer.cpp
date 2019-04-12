#include "qt_application.h"
#include "mainscene.h"
#include "deferredrenderer.h"
#include <QOpenGLFunctions_3_3_Core>
#include "camera.h"
#include "entity.h"
#include "transform.h"

DeferredRenderer::DeferredRenderer()
{

}

bool DeferredRenderer::PassGrid(Camera *camera, std::string path)
{
     //GLenum draw_buffers[] = {GL_COLOR_ATTACHMENT3};
     //glDrawBuffers(1, draw_buffers);

     //OpenGLState glState;
     //glState.depthTest = true;


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

void DeferredRenderer::Render(Camera *camera)
{
    glClearDepth(1.0);
    glClearColor(0.4f,0.4f,0.4f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    PassMeshes(camera);
}

void DeferredRenderer::PassMeshes(Camera *camera)
{
    standard_program.bind();
    standard_program.setUniformValue(standard_program.uniformLocation("projection_matrix"), camera->projection_matrix);
    standard_program.setUniformValue(standard_program.uniformLocation("view_matrix"), camera->view_matrix);

    foreach(Entity* entity, customApp->main_scene()->GetEntities())
    {
        standard_program.setUniformValue(standard_program.uniformLocation("model_matrix"), (*entity->GetTransform()->GetLocalTransform()));
        entity->Draw();
    }

    standard_program.release();

}

void DeferredRenderer::LoadShaders(const char *char_path)
{
    LoadStandardShader(char_path);
    LoadGridShader(char_path);
    LoadBackgroundShader(char_path);
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

void DeferredRenderer::LoadGridShader(const char* char_path)
{
    std::string vertex_path = char_path;
    vertex_path += "/../../CuteEngine/Resources/Shaders/grid_vertex.vert";

    std::string frag_path = char_path;
    frag_path += "/../../CuteEngine/Resources/Shaders/grid_fragment.frag";

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
