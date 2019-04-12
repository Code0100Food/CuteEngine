#ifndef DEFERREDRENDERER_H
#define DEFERREDRENDERER_H

#include <iostream>
#include <QOpenGLShaderProgram>

class Camera;

class DeferredRenderer
{
public:
    DeferredRenderer();

    void Render(Camera *camera);

    void PassMeshes(Camera* camera);
    bool PassGrid(Camera* camera, std::string path);
    void PassBackground(Camera* camera, std::string path);

    void LoadShaders(const char* char_path);
private:
    QOpenGLShaderProgram standard_program;
    void LoadStandardShader(const char* char_path);

    QOpenGLShaderProgram program_grid;
    void LoadGridShader(const char* char_path);

    QOpenGLShaderProgram program_background;
    void LoadBackgroundShader(const char* char_path);



};

#endif // DEFERREDRENDERER_H
