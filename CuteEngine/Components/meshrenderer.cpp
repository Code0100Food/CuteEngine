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

    select_mesh = new QLabel("Selected Mesh: No Selected");
    main_layout->addWidget(select_mesh);

    //QTextEdit* mesh_name = new QTextEdit("Select Mesh");
    //mesh_name->setReadOnly(true);
    //main_layout->addWidget(mesh_name);

    QPushButton* add_mesh = new QPushButton("Add Mesh");
    connect(add_mesh, SIGNAL(clicked(bool)), this, SLOT(SetSelectedMesh()));
    main_layout->addWidget(add_mesh);

    setLayout(main_layout);


    this->type = COMPONENT_MESHRENDERER;
}

void MeshRenderer::SetSelectedMesh()
{
   //Set Mesh
   current_mesh = (Mesh*)customApp->main_window()->resource_manager()->GetSelectedMesh();

   if(current_mesh)
   {
    //Update UI

    std::string tmp = "Selected Mesh: ";
    tmp += current_mesh->GetName();
    select_mesh->setText(tmp.c_str());
   }
}

void MeshRenderer::Update()
{

}

void MeshRenderer::Draw()
{
    if(current_mesh != nullptr)
    {
        current_mesh->Draw();
    }
}
