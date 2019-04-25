#ifndef DEFERREDRENDERER_H
#define DEFERREDRENDERER_H

#include <iostream>
#include <QOpenGLShaderProgram>
#include <QOpenGLFramebufferObject>

class Camera;

class FrameBufferObject
{
public:
    FrameBufferObject(int width, int height, bool has_depth_texture);
    ~FrameBufferObject();

    void Resize(int width, int height);
    void Bind();
    void UnBind();

    unsigned int GetColorTexture() const { return color_texture; }
    unsigned int GetDepthTexture() const { return depth_texture; }
    int GetViewportWidth() const { return viewport_width; }
    int GetViewportHeight() const { return viewport_height; }

private:
    unsigned int frame_buffer = 0;
    unsigned int color_texture = 0;
    unsigned int depth_texture = 0;
    int viewport_width = 0;
    int viewport_height = 0;
};

class DeferredRenderer
{
public:
    DeferredRenderer();
    ~DeferredRenderer();

    void SetMainBuffer(int width, int height);

    void Render(Camera *camera);

    void PassMeshes(Camera* camera);
    bool PassGrid(Camera* camera);
    void PassBackground(Camera* camera);

     FrameBufferObject* main_buffer;

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
