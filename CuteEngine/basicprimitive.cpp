#include "basicprimitive.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <iostream>
#include "circlewidget.h"

BasicPrimitive::BasicPrimitive(E_PRIMITIVE_TYPE _type, QWidget* parent) : Component(parent), primitive_type(_type)
{
    type = COMPONENT_TYPE::COMPONENT_PRIMITIVE;

    switch (_type)
    {
        case  PT_CIRCLE:
            //primitive = (BasicPrimitive*)new CircleWidget();

            break;
        case PT_RECTANGLE:
           // primitive = (BasicPrimitive*)new Rectangle();
            break;
        case PT_STAR:
           // primitive = (BasicPrimitive*)new Star();
            break;
        case PT_MAX_PRIMITIVE:
            std::cout << "Type primitive ERROR" << std::endl;
            break;
    }

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
    select_primitive_box->addItem("Star");

    connect(select_primitive_box, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangePrimitive()));

    layout->addWidget(select_primitive_box);

    layout->addLayout(grid);

    setLayout(layout);
}

BasicPrimitive::~BasicPrimitive()
{
    delete select_primitive_box;
    delete primitive;
}

void BasicPrimitive::paintEvent(QPaintEvent* _event)
{
    //primitive->paintEvent(_event);
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

void BasicPrimitive::ChangePrimitive()
{
    int index = select_primitive_box->currentIndex();
    if (primitive_type != index)
    {
    // TODO: Delete primitive

    // TODO: Create new type primitive
    }
}

E_PRIMITIVE_TYPE BasicPrimitive::GetPrimitiveType() const
{
    return primitive_type;
}

