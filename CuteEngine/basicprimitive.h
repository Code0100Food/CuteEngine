#ifndef BASICPRIMITIVE_H
#define BASICPRIMITIVE_H

#include "component.h"
#include <QColor>
class QPaintEvent;
class QComboBox;

enum E_PRIMITIVE_TYPE
{
    PT_CIRCLE = 0,
    PT_RECTANGLE,
    PT_MAX_PRIMITIVE
};

enum E_LINE_TYPE
{
    LT_SOLID = 0,
    LT_DASH,
    LT_DOT,
    LT_MAX
};

class BasicPrimitive : public Component
{
public:

    BasicPrimitive(E_PRIMITIVE_TYPE _type = PT_CIRCLE, QWidget* parent = nullptr);
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

    void SetLineType(E_LINE_TYPE _type);
    E_LINE_TYPE GetLineType() const;
    Qt::PenStyle QtGetLineType() const;

    E_PRIMITIVE_TYPE GetPrimitiveType() const;

private:

    int x;
    int y;
    int width;
    int height;
    QColor color;
    E_PRIMITIVE_TYPE primitive_type;
    E_LINE_TYPE line_type;

    QComboBox* select_primitive_box;
    QComboBox* select_line_type_box;

public slots:
    void ChangePrimitive();
};

#endif // BASICPRIMITIVE_H
