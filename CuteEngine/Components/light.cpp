#include "light.h"
#include <iostream>

Light::Light()
{
    type = COMPONENT_LIGHT;
    light_color = QVector4D(1.0f, 1.0f, 1.0f, 1.0f);
}

void Light::Update()
{


}

void Light::Draw()
{

}
