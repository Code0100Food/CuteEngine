#include "meshrenderer.h"
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <qt_application.h>
#include <mainwindow.h>
#include <resourcemanager.h>
#include "../Data/mesh.h"

MeshRenderer::MeshRenderer()
{
    //UI initialization
    QVBoxLayout* main_layout = new QVBoxLayout();

    //Window title
    QLabel* title = new QLabel("Mesh Renderer");
    main_layout->addWidget(title);

    QLabel* select_mesh = new QLabel("Selected Mesh: ");
    main_layout->addWidget(select_mesh);

    //QTextEdit* mesh_name = new QTextEdit("Select Mesh");
    //mesh_name->setReadOnly(true);
    //main_layout->addWidget(mesh_name);

    QPushButton* add_mesh = new QPushButton("Add Mesh");
    connect(add_mesh, SIGNAL(clicked(bool)), this, SLOT(SetSelectedMesh()));
    main_layout->addWidget(add_mesh);

    setLayout(main_layout);
}

void MeshRenderer::SetSelectedMesh()
{
   current_mesh = (Mesh*)customApp->main_window()->resource_manager()->GetSelectedMesh();
}

void MeshRenderer::Update()
{
    if(current_mesh != nullptr)
    {
        current_mesh->Draw();
    }
}