#include "component.h"
#include <QPainter>

Component::Component(QWidget* parent) : QWidget(parent)
{
// TODO: Create a transform (must component)
}

Component::~Component()
{

}

void Component::paintEvent(QPaintEvent* aEvent)
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
