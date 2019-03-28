#ifndef MYOPENGLWIDGET_H
#define MYOPENGLWIDGET_H

#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShaderProgram>

class myopenglwidget : public QOpenGLWidget, protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:

    explicit myopenglwidget(QWidget *parent = nullptr);
    ~myopenglwidget()override;

    void initializeGL() override;
    void resizeGL(int width, int height) override;
    void paintGL()override;

private:

    QOpenGLBuffer vbo;
    QOpenGLVertexArrayObject vao;
    QOpenGLShaderProgram program;

signals:

public slots:

    void finalizeGL();

};

#endif // MYOPENGLWIDGET_H

