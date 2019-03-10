#include "component.h"
#include <QPainter>

Component::Component(QWidget* parent) : QWidget(parent)
{

}

Component::~Component()
{

}

COMPONENT_TYPE Component::GetType()const
{
    return type;
}

void Component::ShowUI()
{
    setVisible(true);
}

void Component::HideUI()
{
    hide();
}
