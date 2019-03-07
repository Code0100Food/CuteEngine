#include "basicprimitive.h"

BasicPrimitive::BasicPrimitive(E_PRIMITIVE_TYPE _type, QWidget* parent) : Component(parent), primitive_type(_type)
{

}

BasicPrimitive::~BasicPrimitive()
{

}

void BasicPrimitive::SetX(int _x)
{
    x = _x;
}

void BasicPrimitive::SetY(int _y)
{
    y = _y;
}

void BasicPrimitive::SetWidth(int _width)
{
    width = _width;
}

void BasicPrimitive::SetHeight(int _height)
{
    height = _height;
}

int BasicPrimitive::GetX()const
{
    return x;
}

int BasicPrimitive::GetY()const
{
    return y;
}

int BasicPrimitive::GetWidth()const
{
    return width;
}

int BasicPrimitive::GetHeight()const
{
    return height;
}

void BasicPrimitive::SetColor(QColor _color)
{
    color = _color;
}

const QColor BasicPrimitive::GetColor() const
{
    return color;
}

void BasicPrimitive::ChangePrimitive(E_PRIMITIVE_TYPE _type)
{
    if (primitive_type != _type)
    {
    // TODO: Delete primitive

    // TODO: Create new type primitive
    }
}

const E_PRIMITIVE_TYPE BasicPrimitive::GetPrimitiveType() const
{
    return primitive_type;
}

