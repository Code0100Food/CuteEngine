#ifndef INPUT_H
#define INPUT_H
#include <qwidget.h>

class Input : public QWidget
{
        Q_OBJECT
public:

    Input();

    void keyPressEvent(QKeyEvent *event) override;
    void mouseMoveEvent(QMouseEvent* event) override;
    void mousePressEvent(QMouseEvent* event)override;
};
#endif // INPUT_H
