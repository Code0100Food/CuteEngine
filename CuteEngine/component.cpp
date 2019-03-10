#include "component.h"
#include <QPainter>

Component::Component(QWidget* parent) : QWidget(parent)
{

}

Component::~Component()
{

}

void Component::ShowUI()
{
    setVisible(true);
}

void Component::HideUI()
{
    hide();
}
