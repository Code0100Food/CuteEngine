#include "basicprimitive.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <iostream>
#include <QPainter>

BasicPrimitive::BasicPrimitive(E_PRIMITIVE_TYPE _type, QWidget* parent) : Component(parent), primitive_type(_type), line_type(LT_SOLID)
{
    type = COMPONENT_TYPE::COMPONENT_PRIMITIVE;
    std::cout << "Basic Primitive component created" << std::endl;

    //UI initialization
    QVBoxLayout* layout = new QVBoxLayout();

    //Window title
    QLabel* title = new QLabel("Basic Primitive");
    layout->addWidget(title);

    //Grid
    QGridLayout* grid = new QGridLayout();

    //Combo Box Settings
    select_primitive_box = new QComboBox();
    select_primitive_box->addItem("Circle");
    select_primitive_box->addItem("Rectangle");
    connect(select_primitive_box, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangePrimitive()));
    layout->addWidget(select_primitive_box);

    select_line_type_box = new QComboBox();
    select_line_type_box->addItem("Solid Line");
    //select_line_type_box->addItem()

    layout->addLayout(grid);

    setLayout(layout);
}

BasicPrimitive::~BasicPrimitive()
{
    delete select_primitive_box;
    delete select_line_type_box;
}

void BasicPrimitive::paintEvent(QPaintEvent* _event)
{
    QPainter painter(this);

    QBrush Brush;
    QPen Pen;

    // Brush/Pen configuration
    Brush.setColor(GetColor());
    Brush.setStyle(Qt::BrushStyle::SolidPattern);
    Pen.setStyle(QtGetLineType());
    painter.setBrush(Brush);
    painter.setPen(Pen);

    // Draw
    QRect Rect(GetX(), GetY(), GetWidth(), GetHeight());
    switch (primitive_type)
    {
        case  PT_CIRCLE:
            painter.drawEllipse(Rect);
            break;
        case PT_RECTANGLE:
            painter.drawRect(Rect);
            break;
        case PT_MAX_PRIMITIVE:
            std::cout << "Type primitive ERROR" << std::endl;
            break;
    }

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

void BasicPrimitive::SetLineType(E_LINE_TYPE _type)
{
    line_type = _type;
}

E_LINE_TYPE BasicPrimitive::GetLineType() const
{
    return line_type;
}

Qt::PenStyle BasicPrimitive::QtGetLineType() const
{
    Qt::PenStyle ret = Qt::PenStyle::NoPen;

    switch (line_type)
    {
        case LT_SOLID:
            ret = Qt::PenStyle::SolidLine;
            break;
        case LT_DASH:
            ret = Qt::PenStyle::DashLine;
            break;
        case LT_DOT:
            ret = Qt::PenStyle::DotLine;
            break;
        case LT_MAX:
            std::cout << "QtGetLineType Value not contempled" << std::endl;
            break;
    }

    return ret;
}

void BasicPrimitive::ChangePrimitive()
{
    int index = select_primitive_box->currentIndex();
    if (primitive_type != index)
    {
        primitive_type = (E_PRIMITIVE_TYPE)index;
    }
}

E_PRIMITIVE_TYPE BasicPrimitive::GetPrimitiveType() const
{
    return primitive_type;
}

