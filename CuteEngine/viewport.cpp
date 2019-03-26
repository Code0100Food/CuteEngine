#include "viewport.h"
#include <QPainter>
#include <iostream>
#include <list>
#include"qt_application.h"
#include "mainscene.h"
#include "entity.h"
#include "basicprimitive.h"

Viewport::Viewport(QWidget *parent) : QWidget(parent)
{

}

void Viewport::paintEvent(QPaintEvent* _event)
{
    //Collect all scene entities
    const std::list<Entity*> entities = customApp->main_scene()->GetEntities();
    //Iterate scene entities
    for(std::list<Entity*>::const_iterator entity = entities.begin(); entity != entities.end(); entity++)
    {
        BasicPrimitive* primitive = (BasicPrimitive*)((Entity*)(*entity))->FindComponent(COMPONENT_TYPE::COMPONENT_PRIMITIVE);
        if(primitive != nullptr)
        {
            PaintPrimitive(primitive);
        }
    }
}

void Viewport::PaintPrimitive(const BasicPrimitive *target)
{
    QPainter painter(this);

    QBrush Brush;
    QPen Pen;

    // Brush/Pen configuration
    Brush.setColor(target->GetColor());
    Brush.setStyle(Qt::BrushStyle::SolidPattern);
    int edge_width = target->GetEdgeWidth();
    if(edge_width <= 0)
    {
        Pen.setStyle(Qt::PenStyle::NoPen);
    }
    else
    {
        Pen.setStyle(target->QtGetLineType());
        Pen.setWidth(edge_width);
        Pen.setColor(target->GetEdgeColor());
    }

    painter.setBrush(Brush);
    painter.setPen(Pen);

    painter.save();

    painter.translate(target->GetX() + target->GetWidth() * 0.5, target->GetY() + target->GetHeight() * 0.5);

    painter.rotate(static_cast<double>(target->GetRotation()));

    // Draw
    QRect Rect(- target->GetWidth() * 0.5, - target->GetHeight() * 0.5,target->GetWidth(),target->GetHeight());

    switch (target->GetPrimitiveType())
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

    painter.restore();
}

