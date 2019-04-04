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
    const float drag_scale = 0.1f;
    const float scroll_scale = 0.0010f;
    const float key_move_scale = 0.4f;

    //Buttons
    mutable bool mouse_mid = false;
    mutable bool alt_key = false;
    mutable QPoint mouse_pos;

};
#endif // INPUT_H
