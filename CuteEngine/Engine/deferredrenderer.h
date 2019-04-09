#ifndef DEFERREDRENDERER_H
#define DEFERREDRENDERER_H

#include <iostream>

class Camera;
class QOpenGLShaderProgram;

class DeferredRenderer
{
public:
    DeferredRenderer();

    bool PassGrid(Camera* camera, std::string path);

private:
    QOpenGLShaderProgram* program_grid;

};

#endif // DEFERREDRENDERER_H
