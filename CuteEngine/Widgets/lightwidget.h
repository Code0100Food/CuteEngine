#ifndef LIGHTWIDGET_H
#define LIGHTWIDGET_H

#include <QWidget>
#include <QColor>
#include <QSlider>

class QComboBox;
class QLabel;
class QPushButton;
class Entity;

class LightWidget : public QWidget
{
    Q_OBJECT
public:
    LightWidget();

    QColor GetColor() const { return color; }
    int GetIntensity() const { return light_intensity->value(); }
    int GetRadius() const { return light_radius->value(); }

    void SetIntensity(int value);
    void SetColor(QColor value);
    void SetType(int value);
    void SetRadius(int value);

private:
    QLabel* select_light_type = nullptr;
    QComboBox* light_type = nullptr;

    QLabel* intensity = nullptr;
    QSlider* light_intensity = nullptr;

    //Color
    QPushButton* color_picker = nullptr;
    QColor color;

    //Only for point light
    QLabel* radius_label = nullptr;
    QLabel* radius_label_value = nullptr;
    QSlider* light_radius = nullptr;

    void ChangeLightType(int);

public slots:

    void ChangedLightType(int);
    void ChangedIntensity();
    void ChangedRadius();
    void ChangedColor();
};

#endif // LIGHTWIDGET_H
