#ifndef LIGHT_H
#define LIGHT_H

#include <QVector4D>
#include "component.h"

enum LIGHTTYPE
{
    OFF = 0,
    DIRECTIONAL,
    SPOT
};

class Light : public Component
{
public:
    Light();

    void SetType(LIGHTTYPE _type) { light_type = _type; }
    LIGHTTYPE GetType() const { return light_type; }

private:
    LIGHTTYPE light_type;
    QVector4D LIGHT_COLOR;

    int intensity = 1;
    float radius = 0.0f;
};

#endif // LIGHT_H
