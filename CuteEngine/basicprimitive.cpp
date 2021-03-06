#include "basicprimitive.h"
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QComboBox>
#include <iostream>
#include <QPainter>
#include <transform.h>
#include <QSpinBox>
#include <QPushButton>

BasicPrimitive::BasicPrimitive(E_PRIMITIVE_TYPE _type) : primitive_type(_type), line_type(LT_SOLID)
{
    type = COMPONENT_TYPE::COMPONENT_PRIMITIVE;
    std::cout << "Basic Primitive component created" << std::endl;

    //UI initialization
    layout = new QVBoxLayout();

    //Window title
    title = new QLabel("Basic Primitive");
    layout->addWidget(title);

    //Combo Box Settings
    select_primitive_box = new QComboBox();
    select_primitive_box->addItem("Circle");
    select_primitive_box->addItem("Rectangle");
    //connect(select_primitive_box, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangePrimitive()));
    layout->addWidget(select_primitive_box);

    //Line type
    select_line_type_box = new QComboBox();
    select_line_type_box->addItem("Solid Line");
    select_line_type_box->addItem("Dash Line");
    select_line_type_box->addItem("Dot Line");
    //connect(select_line_type_box, SIGNAL(currentIndexChanged(int)), this, SLOT(SetLineTypeComboBox()));
    layout->addWidget(select_line_type_box);

    //Edge width
    edge_width_label = new QLabel("Edge Width:");
    layout->addWidget(edge_width_label);
    edge_width_spin_box = new QSpinBox();
    edge_width_spin_box->setValue(GetEdgeWidth());
//    connect(edge_width_spin_box, SIGNAL(valueChanged(int)), this, SLOT(SetEdgeWidth(int)));
    layout->addWidget(edge_width_spin_box);

    //Color picker
    pick_color_btn = new QPushButton("Pick Color");
   // connect(pick_color_btn, SIGNAL(clicked(bool)), this, SLOT(SetColorFromColorPicker()));
    layout->addWidget(pick_color_btn);

    //Edge color picker
    pick_edge_color_btn = new QPushButton("Pick Edge Color");
//    connect(pick_edge_color_btn, SIGNAL(clicked(bool)), this, SLOT(SetEdgeColorFromColorPicker()));
    layout->addWidget(pick_edge_color_btn);

    //setLayout(layout);
}

BasicPrimitive::~BasicPrimitive()
{
    delete layout;
    delete title;
    delete select_primitive_box;
    delete select_line_type_box;
    delete edge_width_label;
    delete edge_width_spin_box;
    delete pick_color_btn;
    delete pick_edge_color_btn;
}

void BasicPrimitive::Update()
{
    //this->update();
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

float BasicPrimitive::GetRotation() const
{
    return rotation;
}

void BasicPrimitive::SetColor(QColor _color)
{
    color = _color;
}

void BasicPrimitive::SetEdgeColor(QColor _edge_color)
{
    edge_color = _edge_color;
}

const QColor BasicPrimitive::GetColor() const
{
    return color;
}

const QColor BasicPrimitive::GetEdgeColor() const
{
    return edge_color;
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

int BasicPrimitive::GetEdgeWidth() const
{
    return edge_width;
}

E_PRIMITIVE_TYPE BasicPrimitive::GetPrimitiveType() const
{
    return primitive_type;
}

void BasicPrimitive::Connect(Transform* target_trans)
{
    //Transform Conections
    //connect(target_trans->GetPositionXButton(),SIGNAL(valueChanged(double)),this,SLOT(SetXPosition(double)));
    //connect(target_trans->GetPositionYButton(),SIGNAL(valueChanged(double)),this,SLOT(SetYPosition(double)));
    //
    //connect(target_trans->GetScaleXButton(),SIGNAL(valueChanged(double)),this,SLOT(SetXScale(double)));
    //connect(target_trans->GetScaleYButton(),SIGNAL(valueChanged(double)),this,SLOT(SetYScale(double)));
    //
    //connect(target_trans->GetRotationZButton(),SIGNAL(valueChanged(double)),this,SLOT(SetRotation(double)));
}

void BasicPrimitive::SetTransformValues(Transform *target_trans)
{
    this->x = target_trans->GetPosition().x();
    this->y = target_trans->GetPosition().y();

    this->width = PRIMITIVE_SIZE * target_trans->GetScale().x();
    this->height = PRIMITIVE_SIZE * target_trans->GetScale().y();
}

void BasicPrimitive::SetXPosition(double value)
{
    x = static_cast<float>(value);
}

void BasicPrimitive::SetYPosition(double value)
{
   y = static_cast<float>(value);
}

void BasicPrimitive::SetXScale(double value)
{
   width = PRIMITIVE_SIZE * static_cast<float>(value);
}

void BasicPrimitive::SetYScale(double value)
{
   height = PRIMITIVE_SIZE * static_cast<float>(value);
}

void BasicPrimitive::SetRotation(double value)
{
    rotation = static_cast<float>(value);
}

void BasicPrimitive::ChangePrimitive()
{
    int index = select_primitive_box->currentIndex();
    if (primitive_type != index)
    {
        primitive_type = (E_PRIMITIVE_TYPE)index;
    }
}

void BasicPrimitive::SetLineTypeComboBox()
{
    int index = select_line_type_box->currentIndex();
    if (line_type != index)
    {
        line_type = (E_LINE_TYPE)index;
    }
}

void BasicPrimitive::SetColorFromColorPicker()
{
    ColorDialog color_dialog;
    SetColor(color_dialog.PickColor());
}

void BasicPrimitive::SetEdgeColorFromColorPicker()
{
    ColorDialog color_dialog;
    SetEdgeColor(color_dialog.PickColor());
}

void BasicPrimitive::SetEdgeWidth(int value)
{
    edge_width = value;
}
