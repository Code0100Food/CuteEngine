#include "meshrenderewidget.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGridLayout>
#include <QComboBox>
#include <QGridLayout>
#include "qt_application.h"
#include "mainwindow.h"
#include "resourcemanager.h"
#include "mainscene.h"
#include "Data/mesh.h"
#include "mainscene.h"
#include "entity.h"
#include "meshrenderer.h"
#include "Data/texture.h"

MeshRendereWidget::MeshRendereWidget()
{
    //UI initialization
    QVBoxLayout* main_layout = new QVBoxLayout();

    QGridLayout* grid = new QGridLayout();

    //Window title
    QLabel* title = new QLabel("Mesh Renderer");
    main_layout->addWidget(title);

    select_mesh = new QLabel("Selected Mesh: ");
    grid->addWidget(select_mesh, 0, 0);

    mesh_selector = new QComboBox();
    mesh_selector->addItem("No Mesh Selected");
    grid->addWidget(mesh_selector, 0, 1);

    texture_selector = new QComboBox();
    texture_selector->addItem("No texture");
    grid->addWidget(texture_selector, 1, 1);

    connect(mesh_selector, SIGNAL(currentIndexChanged(int)), this, SLOT(SetSelectedMesh(int)));
    connect(texture_selector, SIGNAL(currentIndexChanged(int)), this, SLOT(SetSelectedTexture(int)));

    main_layout->addLayout(grid);
    setLayout(main_layout);
}

void MeshRendereWidget::AddMesh(const char* name)
{
    mesh_selector->addItem(name);
}

void MeshRendereWidget::SetSelectedMesh(int value) const
{
    if(value == 0)
        return;

    //Esto no me gusta pero es fast de hacer
    Mesh* selected_mesh = (Mesh*)customApp->main_window()->resource_manager()->GetResourceByName(mesh_selector->currentText().toStdString(), RESOURCE_MESH);

    Entity* tmp = customApp->main_scene()->GetSelectedEntity();
    if(tmp)
    {
        std::cout<< mesh_selector->currentText().toStdString() << std::endl;

        MeshRenderer* entity_mesh_renderer = (MeshRenderer*)tmp->FindComponent(COMPONENT_TYPE::COMPONENT_MESHRENDERER);
        entity_mesh_renderer->SetCurrentMesh(selected_mesh);
    }
}

void MeshRendereWidget::SetSelectedTexture(int value) const
{
    if(value == 0)
        return;

    //Esto no me gusta pero es fast de hacer
    std::cout<< "Looking for " << mesh_selector->currentText().toStdString() << std::endl;
    Texture* selected_texture = (Texture*)customApp->main_window()->resource_manager()->GetResourceByName("Skin_Patrick.png", RESOURCE_TYPE::RESOURCE_TEXTURE);

    if(selected_texture)
        std::cout<<"Texture nonull"<<std::endl;

    selected_texture->GetIndex();

    Entity* tmp = customApp->main_scene()->GetSelectedEntity();
    if(tmp)
    {
        std::cout<< mesh_selector->currentText().toStdString() << std::endl;

        MeshRenderer* entity_mesh_renderer = (MeshRenderer*)tmp->FindComponent(COMPONENT_TYPE::COMPONENT_MESHRENDERER);
        entity_mesh_renderer->debug = selected_texture;
        std::cout << "selected texture" << std::endl;
    }
}

void MeshRendereWidget::ResetComboBox()
{
    mesh_selector->setCurrentIndex(0);
}

void MeshRendereWidget::UpdateComboBox(const char *name)
{
    mesh_selector->setCurrentIndex( mesh_selector->findText(name));
}
























