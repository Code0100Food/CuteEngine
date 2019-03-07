#include "inspector.h"
#include "qt_application.h"
#include "mainscene.h"
#include <QVBoxLayout>
#include <QComboBox>
#include "entity.h"
#include "transform.h"
#include "basicprimitive.h"

Inspector::Inspector(QWidget* parent) : QWidget(parent)
{
    Start();
}

Inspector::~Inspector()
{

}

void Inspector::Start()
{
    layout = new QVBoxLayout();

    add_component_button = new QComboBox();
    add_component_button->addItem("Add Component");
    add_component_button->addItem("Transform");
    add_component_button->addItem("Basic Primitive");

    connect(add_component_button,SIGNAL(currentIndexChanged(int)),this,SLOT(AddComponent()));

    layout->addWidget(add_component_button);

    setLayout(layout);
}

void Inspector::AddComponent()
{
    int index = add_component_button->currentIndex();

    switch (index)
    {
    case 1:
        CreateTransformation();
        break;
    case 2:
        CreateBasicPrimitive();
        break;
    }
}

void Inspector::CreateTransformation()
{
    std::list<Entity*> selected = customApp->main_scene()->GetSelectedEntities();
    for(std::list<Entity*>::const_iterator entity_item = selected.begin(); entity_item != selected.end(); entity_item++)
    {
        Transform* transform = new Transform();
        (*entity_item)->AddComponent(transform);
        layout->addWidget(transform);

        std::cout<<(*entity_item)->GetName()<<std::endl;
    }

    add_component_button->setCurrentIndex(0);
}

void Inspector::CreateBasicPrimitive()
{

    add_component_button->setCurrentIndex(0);
}
