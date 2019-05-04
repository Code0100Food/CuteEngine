#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#define PI 3.14159265358979323846f
#define RADTODEG(angle_in_radiants) (angle_in_radiants*180.0f)/PI
#define DEGTORAD(angle_in_degrees) (angle_in_degrees*PI)/180.0f

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>
#include <camera.h>

class QMatrix4x4;
class QTimer;
class Mesh;
class DeferredRenderer;

enum RENDERMODE
{
    FINAL_COLOR = 0,
    NORMALS,
    DEPTH
};

class myopenglwidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:

    explicit myopenglwidget(QWidget *parent = nullptr);
    ~myopenglwidget()override;

    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

    //Input methods
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event)override;
    void mouseReleaseEvent(QMouseEvent* event)override;
    void wheelEvent(QWheelEvent* event)override;
    void enterEvent(QEvent* event)override;
    void leaveEvent(QEvent* event)override;

    //Camera methods
    void TranslateCamera(float x, float y, float z);
    void RotateCamera(float x, float y, float z);
    QVector3D GetCameraPosition()const;
    QVector3D GetCameraFront()const;

    Camera* GetCamera(){return camera;}

    Mesh* patrick = nullptr;

private:

    //Camera settings
    Camera* camera = nullptr;
    //QMatrix4x4* camera = nullptr;
    //QMatrix4x4* projection = nullptr;

    float aspect_ratio = 0.0f;
    float field_of_view = 90.0f; //radiants
    float near_plane_distance = 0.1f;
    float far_plane_distance = 150.0f;

    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram program;

    DeferredRenderer* deferred_renderer;
    QOpenGLShaderProgram program_grid;

    RENDERMODE render_mode = FINAL_COLOR;

public slots:

    void finalizeGL();

    void ChangeRenderModeColor();
    void ChangeRenderModeNormals();
    void ChangeRenderModeDepth();

};

#endif // MYOPENGLWIDGET_H

