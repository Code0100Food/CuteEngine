#ifndef INPUT_H
#define INPUT_H
#include <qwidget.h>

class myopenglwidget;

class Input : public QWidget
{
        Q_OBJECT
public:

    Input();

    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event)override;

private:

    myopenglwidget* gl_widget = nullptr;

};
#endif // INPUT_H
