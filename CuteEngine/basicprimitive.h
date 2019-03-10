#ifndef BASICPRIMITIVE_H
#define BASICPRIMITIVE_H

#include "component.h"
#include <QColor>
class QPaintEvent;

enum E_PRIMITIVE_TYPE
{
    PT_CIRCLE = 0,
    PT_RECTANGLE,
    PT_STAR,
    PT_MAX_PRIMITIVE
};

class BasicPrimitive : public Component
{
public:

    BasicPrimitive(E_PRIMITIVE_TYPE _type, QWidget* parent = nullptr);
    ~BasicPrimitive() override;

    void paintEvent(QPaintEvent* _event)override;

public:

    void SetX(int _x);
    void SetY(int _y);
    void SetWidth(int _width);
    void SetHeight(int _height);

    int GetX()const;
    int GetY()const;
    int GetWidth()const;
    int GetHeight()const;

    void SetColor(QColor _color);
    const QColor GetColor() const;

    void ChangePrimitive(E_PRIMITIVE_TYPE _type);
    E_PRIMITIVE_TYPE GetPrimitiveType() const;

private:

    int x;
    int y;
    int width;
    int height;
    QColor color;
    E_PRIMITIVE_TYPE primitive_type;
};

#endif // BASICPRIMITIVE_H
