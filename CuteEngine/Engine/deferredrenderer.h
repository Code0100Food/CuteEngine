#ifndef DEFERREDRENDERER_H
#define DEFERREDRENDERER_H

#include <iostream>
#include <QOpenGLShaderProgram>

class Camera;

class DeferredRenderer
{
public:
    DeferredRenderer();

    bool PassGrid(Camera* camera, std::string path);
    void PassBackground(Camera* camera, std::string path);

private:
    QOpenGLShaderProgram program_grid;
    QOpenGLShaderProgram program_background;

};

#endif // DEFERREDRENDERER_H
