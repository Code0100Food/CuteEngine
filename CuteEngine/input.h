#ifndef INPUT_H
#define INPUT_H
#include <qwidget.h>

class myopenglwidget;

class Input : public QWidget
{
        Q_OBJECT
public:

    explicit Input();
    ~Input()override;

    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event)override;
    void mouseReleaseEvent(QMouseEvent* event)override;
    void wheelEvent(QWheelEvent* event)override;

private:

    myopenglwidget* gl_widget = nullptr;

    //Config
    const float drag_scale = 0.10f;

    //Buttons
    mutable bool mouse_mid = false;
    mutable QPoint mouse_pos;

};
#endif // INPUT_H
