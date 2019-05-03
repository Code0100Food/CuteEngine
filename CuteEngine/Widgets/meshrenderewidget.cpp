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
#include "Data/material.h"

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

    QLabel* select_material = new QLabel("Selected Material: ");
    grid->addWidget(select_material, 1, 0);

    texture_selector = new QComboBox();
    texture_selector->addItem("No Material");
    grid->addWidget(texture_selector, 1, 1);

    connect(texture_selector , SIGNAL(currentIndexChanged(int)), this, SLOT(SetSelectedTexture(int)));
    connect(mesh_selector, SIGNAL(currentIndexChanged(int)), this, SLOT(SetSelectedMesh (int)));

    main_layout->addLayout(grid);
    setLayout(main_layout);
}

void MeshRendereWidget::AddMesh(const char* name)
{
    mesh_selector->addItem(name);
}

void MeshRendereWidget::AddMaterial(const char *name)
{
    texture_selector->addItem(name);
}

void MeshRendereWidget::SetSelectedMesh(int value)
{
    if(value == 0)
        return;

    //Esto no me gusta pero es fast de hacer
    Mesh* selected_mesh = (Mesh*)customApp->main_window()->resource_manager()->GetResourceByName(mesh_selector->currentText().toStdString(), RESOURCE_MESH);

    Entity* tmp = customApp->main_scene()->GetSelectedEntity();
    if(tmp)
    {
        MeshRenderer* entity_mesh_renderer = (MeshRenderer*)tmp->FindComponent(COMPONENT_TYPE::COMPONENT_MESHRENDERER);
        entity_mesh_renderer->SetCurrentMesh(selected_mesh);
    }
}

void MeshRendereWidget::SetSelectedTexture(int value)
{
    if(value == 0)
        return;

    //Esto no me gusta pero es fast de hacer
    Material* selected_material = (Material*)customApp->main_window()->resource_manager()->GetResourceByName(texture_selector->currentText().toStdString(), RESOURCE_TYPE::RESOURCE_MATERIAL);

    Entity* tmp = customApp->main_scene()->GetSelectedEntity();
    if(tmp)
    {
        MeshRenderer* entity_mesh_renderer = (MeshRenderer*)tmp->FindComponent(COMPONENT_TYPE::COMPONENT_MESHRENDERER);
        entity_mesh_renderer->SetCurrentMaterial(selected_material);
    }
}

void MeshRendereWidget::ResetComboBox(int type)
{
    switch(type)
    {
        case RESOURCE_MESH:
            mesh_selector->setCurrentIndex(0);
            break;

        case RESOURCE_MATERIAL:
            texture_selector->setCurrentIndex(0);
            break;
    }
}

void MeshRendereWidget::UpdateComboBox(int type, const char *name)
{

    switch(type)
    {
        case RESOURCE_MESH:
             mesh_selector->setCurrentIndex( mesh_selector->findText(name));
            break;

        case RESOURCE_MATERIAL:
            texture_selector->setCurrentIndex(texture_selector->findText(name));
            break;
    }
}
























