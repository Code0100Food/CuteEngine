#include "light.h"
#include <iostream>

Light::Light()
{
    type = COMPONENT_LIGHT;
}

void Light::Update()
{
    std::cout<< "intensity: " << intensity << " radius: " << radius << " type: " << light_type << " Color: " << light_color.x()<< light_color.y()<< light_color.z()<< light_color.w()<< std::endl;

}
