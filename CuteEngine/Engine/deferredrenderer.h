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

    void Create(int width, int height);
    void Destroy();

    unsigned int GetColorTexture() const { return color_texture; }
    unsigned int GetNormalTexture() const { return normals_texture; }
    unsigned int GetShadedTexture() const { return shaded_color; }
    unsigned int GetDepthTexture() const { return depth_texture; }
    unsigned int GetSelectionTexture() const {return selection_texture;}

    int GetViewportWidth() const { return viewport_width; }
    int GetViewportHeight() const { return viewport_height; }

private:
    unsigned int frame_buffer = 0;

    unsigned int color_texture = 0;
    unsigned int normals_texture = 0;
    unsigned int shaded_color = 0;
    unsigned int depth_texture = 0;
    unsigned int selection_texture = 0;
    unsigned int mask_texture = 0;

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
    void Resize(int width, int height);

    void PassMeshes(Camera* camera);
    bool PassGrid(Camera* camera);
    void PassBackground(Camera* camera);
    void PassLights(Camera* camera);
    void ProcessSelection();

     FrameBufferObject* main_buffer;

    void LoadShaders(const char* char_path);

private:
    QOpenGLShaderProgram standard_program;
    void LoadStandardShader(const char* char_path);

    QOpenGLShaderProgram program_grid;
    void LoadGridShader(const char* char_path);

    QOpenGLShaderProgram program_background;
    void LoadBackgroundShader(const char* char_path);

    QOpenGLShaderProgram program_lights;
    void LoadLightsShader(const char* char_path);

    QOpenGLShaderProgram program_selection;
    void LoadSelectionShader(const char* char_path);

    QOpenGLShaderProgram program_mask;
    void LoadMaskShader(const char* char_path);

    GLuint CubeMapId;
    GLsizei resolution;
};

#endif // DEFERREDRENDERER_H
