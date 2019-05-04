#include "inspector.h"
#include "qt_application.h"
#include "mainscene.h"
#include <QVBoxLayout>
#include <QComboBox>
#include "entity.h"
#include "transform.h"
#include "Widgets/transformwidget.h"
#include "basicprimitive.h"
#include <QTextEdit>
#include <QSplitter>
#include "mainwindow.h"
#include <qscrollarea.h>
#include "meshrenderer.h"
#include <QGridLayout>
#include <QPushButton>
#include "Widgets/meshrenderewidget.h"
#include "Data/mesh.h"

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

    //Transform Settings
    transform_widget = new TransformWidget(nullptr);

    //Mesh Renderer Settings
    mesh_renderer_widget = new MeshRendereWidget();
    mesh_renderer_widget->hide();

    //ButTons
    add_mesh_renderer = new QPushButton("Add Mesh Renderer");
    connect(add_mesh_renderer, SIGNAL(released()), this, SLOT(AddMeshRenderer()));

    add_light_source = new QPushButton("Add Light Source");

    QSplitter* tmp = new QSplitter();

    layout->addWidget(name_display);
    layout->addWidget(transform_widget);
    layout->addWidget(mesh_renderer_widget);
    layout->addWidget(tmp);

    layout->addWidget(add_mesh_renderer);
    layout->addWidget(add_light_source);

    setLayout(layout);
}

void Inspector::SetName(QString entity_name)
{
    name_display->setText(entity_name);
}

void Inspector::ShowUI()
{
    //Deprecated
}

void Inspector::HideUI()
{
    //Deprecated
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
    //std::list<Entity*> selected = customApp->main_scene()->GetSelectedEntities();
    //for(std::list<Entity*>::const_iterator entity_item = selected.begin(); entity_item != selected.end(); entity_item++)
    //{
    //    if((*entity_item)->FindComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM))continue;
    //
    //    //Transform* transform = new Transform();
    //    //(*entity_item)->AddComponent(transform);
    //    //layout->addWidget(transform);
    //
    //    std::cout<<(*entity_item)->GetName()<<std::endl;
    //}
    //
    //add_component_button->setCurrentIndex(0);
}

void Inspector::CreateMeshRenderer()
{
    std::list<Entity*> selected = customApp->main_scene()->GetSelectedEntities();
    for(std::list<Entity*>::const_iterator entity_item = selected.begin(); entity_item != selected.end(); entity_item++)
    {
        if((*entity_item)->FindComponent(COMPONENT_TYPE::COMPONENT_MESHRENDERER))continue;

        MeshRenderer* mesh_renderer = new MeshRenderer();
        (*entity_item)->AddComponent(mesh_renderer);
        //layout->addWidget(mesh_renderer);

        std::cout<<(*entity_item)->GetName()<<std::endl;
    }

    add_component_button->setCurrentIndex(0);
}

void Inspector::CreateBasicPrimitive()
{
    //std::list<Entity*> selected = customApp->main_scene()->GetSelectedEntities();
    //for(std::list<Entity*>::const_iterator entity_item = selected.begin(); entity_item != selected.end(); entity_item++)
    //{
    //    if((*entity_item)->FindComponent(COMPONENT_TYPE::COMPONENT_PRIMITIVE))continue;
    //
    //    BasicPrimitive* primitive = new BasicPrimitive(E_PRIMITIVE_TYPE::PT_CIRCLE);
    //    (*entity_item)->AddComponent(primitive);
    //    primitive->GoToInspector(layout);
    //
    //    Transform* target_trans = dynamic_cast<Transform*>((*entity_item)->FindComponent(COMPONENT_TYPE::COMPONENT_TRANSFORM));
    //    primitive->Connect(target_trans);
    //    primitive->SetTransformValues(target_trans);
    //
    //    std::cout<<(*entity_item)->GetName()<<std::endl;
    //}
    //
    //add_component_button->setCurrentIndex(0);
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

void Inspector::UIReadEntity(Entity *selected_entity)
{
    Transform* entity_transform = selected_entity->GetTransform();

    transform_widget->SetSelectedTransform(entity_transform);
    transform_widget->GetEntityValues(entity_transform->GetPosition(), entity_transform->GetRotation(), entity_transform->GetScale());

    MeshRenderer* entity_renderer = (MeshRenderer*)selected_entity->FindComponent(COMPONENT_TYPE::COMPONENT_MESHRENDERER);

    if(entity_renderer)
    {
        mesh_renderer_widget->show();
        add_mesh_renderer->hide();

        //Update mesh Combo Box
        if(!entity_renderer->GetCurrentMesh())
            mesh_renderer_widget->ResetComboBox(RESOURCE_MESH);
        else mesh_renderer_widget->UpdateComboBox(RESOURCE_MESH, entity_renderer->GetCurrentMesh()->GetName());

        //Updtae material Combo Box
       if(!entity_renderer->GetCurrentMaterial())
           mesh_renderer_widget->ResetComboBox(RESOURCE_MATERIAL);
       else mesh_renderer_widget->UpdateComboBox(RESOURCE_MATERIAL, entity_renderer->GetCurrentMesh()->GetName());

    }
    else
    {
        add_mesh_renderer->show();
        mesh_renderer_widget->hide();
    }
}

void Inspector::AddMeshToWidget(const char *name)
{
    mesh_renderer_widget->AddMesh(name);
}

void Inspector::AddMaterialToWidget(const char *name)
{
    mesh_renderer_widget->AddMaterial(name);
}

void Inspector::AddMeshRenderer()
{
    Entity* tmp = customApp->main_scene()->GetSelectedEntity();

    if(tmp)
    {
        MeshRenderer* new_mesh_renderer = new MeshRenderer();
        tmp->AddComponent(new_mesh_renderer);

        mesh_renderer_widget->show();
        add_mesh_renderer->hide();

        mesh_renderer_widget->ResetComboBox(RESOURCE_MESH);
        mesh_renderer_widget->ResetComboBox(RESOURCE_MATERIAL);
    }
}
