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
    Pen.setStyle(target->QtGetLineType());
    Pen.setWidth(target->GetEdgeWidth());
    painter.setBrush(Brush);
    painter.setPen(Pen);

    // Draw
    QRect Rect(target->GetX(),target->GetY(),target->GetWidth(),target->GetHeight());
    painter.drawEllipse(Rect);
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
}

