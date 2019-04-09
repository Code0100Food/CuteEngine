#include "deferredrenderer.h"
#include <QOpenGLShaderProgram>

DeferredRenderer::DeferredRenderer()
{

}

bool DeferredRenderer::PassGrid(Camera *camera, std::string path)
{
//    GLenum draw_buffers[] = {GL_COLOR_ATTACHMENT3};
//    glDrawBuffers(1, draw_buffers);
//
//    OpenGLState glState;
//    glState.depthTest = true;
//
//    std::string grid_vertex_path = path + "/../../CuteEngine/Resources/Shaders/standard_vertex.vert";
//    std::string grid_frag_path = path + "/../../CuteEngine/Resources/Shaders/standard_fragment.frag";
//
//    program_grid->create();
//    program_grid->addShaderFromSourceFile(QOpenGLShader::Vertex, grid_vertex_path.c_str());
//    program_grid->addShaderFromSourceFile(QOpenGLShader::Fragment, grid_frag_path.c_str());
//
//    program_grid->link();
//    if (program_grid->bind())
//    {
//        QVector4D camera_parameters; // = camera->GetLRBT();
//        program_grid->setUniformValue("left", camera_parameters.x());
//        program_grid->setUniformValue("right", camera_parameters.y());
//        program_grid->setUniformValue("bottom", camera_parameters.z());
//        program_grid->setUniformValue("top", camera_parameters.w());
//        program_grid->setUniformValue("znear", camera->;
//        program_grid->setUniformValue("worldMatrix", camera->a());
//        program_grid->setUniformValue("viewMatrix", camera->a());
//        program_grid->setUniformValue("projectionMatrix", camera->a());
//
//        resource_manager->quad->submeshes[0]->draw();
//
//        program_grid->release();
//    }
    return true;
}
