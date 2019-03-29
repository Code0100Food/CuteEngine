#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#define PI 3.14159265358979323846f

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

class QMatrix4x4;
class QTimer;

class myopenglwidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:

    explicit myopenglwidget(QWidget *parent = nullptr);
    ~myopenglwidget()override;

    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL() override;

    void keyPressEvent(QKeyEvent *event) override;



private:
    QTimer* update_timer = nullptr;

    //Camera settings
    QMatrix4x4* camera = nullptr;

    float field_of_view = 45.0f; //radiants
    float near_plane_distance = 0.1f;
    float far_plane_distance = 150.0f;

    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram program;

signals:

public slots:

    void finalizeGL();

};

#endif // MYOPENGLWIDGET_H

