#include <QComboBox>
#include <QGridLayout>
#include "environment.h"
#include "qt_application.h"
#include "mainwindow.h"
#include "resourcemanager.h"
#include "../Data/texture.h"

Environment::Environment(QWidget* parent) : QWidget(parent)
{
    layout = new QGridLayout();
    select_texture_combo_box = new QComboBox();
    select_texture_combo_box->addItem("No Texture");
    layout->addWidget(select_texture_combo_box, 0, 0, Qt::AlignmentFlag::AlignTop);

    setLayout(layout);

    connect(select_texture_combo_box , SIGNAL(currentIndexChanged(int)), this, SLOT(SetSelectedTexture(int)));
}

Environment::~Environment()
{
    if(select_texture_combo_box != nullptr)
        delete select_texture_combo_box;
}

void Environment::AddHDRTexture(const char *name)
{
    select_texture_combo_box->addItem(name);
}

void Environment::SetSelectedTexture(int value)
{
    if(value == 0)
        return;

    //Esto no me gusta pero es fast de hacer (V2.0)
    texture = (Texture*)customApp->main_window()->resource_manager()->GetResourceByName(select_texture_combo_box->currentText().toStdString(), RESOURCE_TYPE::RESOURCE_HDR_TEXTURE);

    //Entity* tmp = customApp->main_scene()->GetSelectedEntity();
    //if(tmp)
    //{
    //    MeshRenderer* entity_mesh_renderer = (MeshRenderer*)tmp->FindComponent(COMPONENT_TYPE::COMPONENT_MESHRENDERER);
    //    entity_mesh_renderer->SetCurrentMaterial(selected_material);
    //}
}

void Environment::UpdateComboBox(int type, const char *name)
{
    if((RESOURCE_TYPE)type == RESOURCE_MATERIAL)
    {
        select_texture_combo_box->setCurrentIndex(select_texture_combo_box->findText(name));
        return;
    }
}
