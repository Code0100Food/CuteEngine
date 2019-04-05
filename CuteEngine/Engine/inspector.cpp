#include "inspector.h"
#include "qt_application.h"
#include "mainscene.h"
#include <QVBoxLayout>
#include <QComboBox>
#include "entity.h"
#include "transform.h"
#include "basicprimitive.h"
#include <QTextEdit>
#include <QSplitter>
#include "mainwindow.h"
#include <qscrollarea.h>
#include "meshrenderer.h"

Inspector::Inspector(QWidget* parent) : QWidget(parent)
{
    Start();
}

Inspector::~Inspector()
{
    delete add_component_button;
    delete name_display;
    delete layout;
}

void Inspector::Start()
{
    //QScrollArea* scroll = new QScrollArea(this);

    layout = new QVBoxLayout();

    //Entity Name Display
    name_display = new QTextEdit();
    name_display->setMaximumHeight(30);
    name_display->setFontPointSize(12);

    connect(name_display, SIGNAL(textChanged()), this, SLOT(Rename()));

    //Combo Box Settings
    add_component_button = new QComboBox();
    add_component_button->addItem("Add Component");
    add_component_button->addItem("Transform");
    add_component_button->addItem("Mesh Renderer");

    connect(add_component_button,SIGNAL(currentIndexChanged(int)),this,SLOT(AddComponent()));

    QSplitter* tmp = new QSplitter();

    layout->addWidget(name_display);
    layout->addWidget(add_component_button);
    layout->addWidget(tmp);

    setLayout(layout);

    HideUI();
}

void Inspector::SetName(QString entity_name)
{
    name_display->setText(entity_name);
}

void Inspector::ShowUI()
{
    name_display->show();
    add_component_button->show();
}

void Inspector::HideUI()
{
    name_display->hide();
    add_component_button->hide();
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
        std::cout<<"Create Mesh Renderer" << std::endl;
        CreateMeshRenderer();
        break;
    case 3:
        CreateBasicPrimitive();
        break;
    }
}

void Inspector::CreateTransformation()
{
    std::list<Entity*> selected = customApp->main_scene()->GetSelectedEntities();
    for(std::list<Entity*>::const_iterator entity_item = selected.begin(); entity_item != selected.end(); entity_item++)
    {
        if((*entity_item)->FindComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM))continue;

        Transform* transform = new Transform();
        (*entity_item)->AddComponent(transform);
        layout->addWidget(transform);

        std::cout<<(*entity_item)->GetName()<<std::endl;
    }

    add_component_button->setCurrentIndex(0);
}

void Inspector::CreateMeshRenderer()
{
    std::list<Entity*> selected = customApp->main_scene()->GetSelectedEntities();
    for(std::list<Entity*>::const_iterator entity_item = selected.begin(); entity_item != selected.end(); entity_item++)
    {
        if((*entity_item)->FindComponent(COMPONENT_TYPE::COMPONENT_MESHRENDERER))continue;

        MeshRenderer* mesh_renderer = new MeshRenderer();
        (*entity_item)->AddComponent(mesh_renderer);
        layout->addWidget(mesh_renderer);

        std::cout<<(*entity_item)->GetName()<<std::endl;
    }

    add_component_button->setCurrentIndex(0);
}

void Inspector::CreateBasicPrimitive()
{
    std::list<Entity*> selected = customApp->main_scene()->GetSelectedEntities();
    for(std::list<Entity*>::const_iterator entity_item = selected.begin(); entity_item != selected.end(); entity_item++)
    {
        if((*entity_item)->FindComponent(COMPONENT_TYPE::COMPONENT_PRIMITIVE))continue;

        BasicPrimitive* primitive = new BasicPrimitive(E_PRIMITIVE_TYPE::PT_CIRCLE);
        (*entity_item)->AddComponent(primitive);
        primitive->GoToInspector(layout);

        Transform* target_trans = dynamic_cast<Transform*>((*entity_item)->FindComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
        primitive->Connect(target_trans);
        primitive->SetTransformValues(target_trans);

        std::cout<<(*entity_item)->GetName()<<std::endl;
    }

    add_component_button->setCurrentIndex(0);
} 

void Inspector::Rename()
{
    std::string tmp = name_display->toPlainText().toStdString();

    if(tmp.size() > 0 && tmp.at(tmp.size() - 1) == '\n')
    {
       name_display->setText(tmp.substr(0, tmp.size()-1).c_str());
       std::cout<<name_display->toPlainText().toStdString()<<std::endl;

       customApp->main_scene()->RenameSelectedEntity(name_display->toPlainText().toStdString());
    }
}

