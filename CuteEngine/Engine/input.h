#ifndef INPUT_H
#define INPUT_H
#include <qwidget.h>

class myopenglwidget;

class Input
{
public:

    explicit Input();
    ~Input();

    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void wheelEvent(QWheelEvent* event);
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);

private:

    myopenglwidget* gl_widget = nullptr;

    //Config
    const float drag_speed = 0.001f;
    const float scroll_speed = 0.02f;
    const float rotation_speed = 0.05f;
    const float wasd_speed = 0.01f;

    //Buttons
    mutable bool mouse_mid = false;
    mutable bool alt_key = false;
    mutable bool right_mouse = false;
    mutable bool left_mouse = false;

    mutable QPoint mouse_pos;

    int mouse_x = 0;
    int mouse_y = 0;
    int mouse_prev_x = 0;
    int mouse_prev_y = 0;
};
#endif // INPUT_H
