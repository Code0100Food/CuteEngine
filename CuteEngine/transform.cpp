#include "transform.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>

Transform::Transform(QWidget *aParent) : Component(aParent)
{
    type = COMPONENT_TYPE::COMPONENT_TRANSFORM;

    //setAutoFillBackground(true);

    QVBoxLayout* layout = new QVBoxLayout();

    QPushButton* add_entity = new QPushButton("Add Entity");

    layout->addWidget(add_entity);
    setLayout(layout);
}

Transform::~Transform()
{

}
