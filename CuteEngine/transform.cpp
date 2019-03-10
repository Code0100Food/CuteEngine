#include "transform.h"
#include <QPushButton>
#include <QVBoxLayout>

Transform::Transform(QWidget *aParent) : Component(aParent)
{
    type = COMPONENT_TYPE::COMPONENT_TRANSFORM;

    //setAutoFillBackground(true);

    QVBoxLayout* layout = new QVBoxLayout();

    QPushButton* add_entity = new QPushButton("Add Entity");

    layout->addWidget(add_entity);
    setLayout(layout);
}

void Transform::paintEvent(QPaintEvent* aEvent)
{

}
