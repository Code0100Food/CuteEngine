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

MeshRendereWidget::MeshRendereWidget()
{
    //UI initialization
    QVBoxLayout* main_layout = new QVBoxLayout();

    QGridLayout* grid = new QGridLayout();

    //Window title
    QLabel* title = new QLabel("Mesh Renderer");
    main_layout->addWidget(title);

    select_mesh = new QLabel("Selected Mesh: No Selected");
    grid->addWidget(select_mesh, 0, 0);

    mesh_selector = new QComboBox();
    mesh_selector->addItem("No Mesh Selected");
    grid->addWidget(mesh_selector, 0, 1);

    connect(mesh_selector, SIGNAL(currentIndexChanged(int)), this, SLOT(SetSelectedMesh(int)));

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
    Mesh* selected_mesh = (Mesh*)customApp->main_window()->resource_manager()->GetMeshByName(mesh_selector->currentText().toStdString());

    Entity* tmp = customApp->main_scene()->GetSelectedEntity();
    if(tmp)
    {
        std::cout<< mesh_selector->currentText().toStdString() << std::endl;

        MeshRenderer* entity_mesh_renderer = (MeshRenderer*)tmp->FindComponent(COMPONENT_TYPE::COMPONENT_MESHRENDERER);
        entity_mesh_renderer->SetCurrentMesh(selected_mesh);
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
























