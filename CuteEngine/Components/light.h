#ifndef LIGHT_H
#define LIGHT_H

#include <QVector4D>
#include "component.h"

enum LIGHTTYPE
{
    DIRECTIONAL = 0,
    SPOT
};

class Light : public Component
{
public:
    Light();

    void SetType(LIGHTTYPE _type) { light_type = _type; }
    void SetColor(QVector4D _color) { light_color = _color; }
    void SetIntensity(int _intensity) { intensity = _intensity; }
    void SetRadius(int _radius) { radius = _radius; }

    LIGHTTYPE GetType() const { return light_type; }
    QVector4D GetColor() const { return light_color; }
    int GetIntensity() const { return intensity; }
    int GetRadius() const { return radius; }

    void Update() override;

private:
    LIGHTTYPE light_type = DIRECTIONAL;
    QVector4D light_color;

    int intensity = 1;
    int radius = 0.0f;
};

#endif // LIGHT_H
