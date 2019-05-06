#ifndef LIGHTWIDGET_H
#define LIGHTWIDGET_H

#include <QWidget>

class QComboBox;
class QLabel;

class LightWidget : public QWidget
{
    Q_OBJECT
public:
    LightWidget();

    QLabel* select_light_type = nullptr;
    QComboBox* light_type = nullptr;

};

#endif // LIGHTWIDGET_H
