#include "resourcemanager.h"
#include "iostream"
#include "../Data/mesh.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myopenglwidget.h"
#include "qt_application.h"
#include <QListWidget>
#include <QLabel>

ResourceManager::ResourceManager(QWidget* parent) : QWidget(parent)
{
    widget_resources_list = new QListWidget(parent);

    QVBoxLayout* _layout = new QVBoxLayout();
    _layout->addWidget(widget_resources_list);

    setLayout(_layout);
}

void ResourceManager::Import(std::string path)
{
    //Check file type
    if(path.substr(path.find_last_of(".")) == ".obj")
        ImportMesh(path);

}

void ResourceManager::ImportMesh(std::string path)
{
    Mesh* new_mesh = new Mesh();
    new_mesh->SetName(path.substr(path.find_last_of("/") + 1).c_str());
    new_mesh->LoadModel(path.c_str());    
    std::cout<< "LOADED MESH: " << path.substr(path.find_last_of("/") + 1).c_str()<<std::endl;

    //Add the new mesh to the resources list
    resources.push_back(new_mesh);

    //Add the new mesh to the UI
    widget_resources_list->addItem(new_mesh->GetName());

}

void ResourceManager::DebugDraw() const
{
    for(std::list<Resource*>::const_iterator i = resources.begin(); i != resources.end(); i++)
    {
        if(!(*i)->NeedsReload())
            (*i)->Draw();      
    }
}

void ResourceManager::UpdateResources()
{
    for(std::list<Resource*>::const_iterator i = resources.begin(); i != resources.end(); i++)
    {
        if((*i)->NeedsReload())
        {
            customApp->main_window()->uiMain()->openGLWidget->makeCurrent();
            (*i)->Reload();
        }
    }
}

Resource* ResourceManager::GetSelectedMesh() const
{
    QList<QListWidgetItem*> selected_items = widget_resources_list->selectedItems();

    if(selected_items.size() <= 0)
    {
        std::cout<<"NO RESOURCE MESH SELECTED"<< std::endl;
        return nullptr;
    }
    if(selected_items.size() > 1)
    {
        std::cout<<"MORE THAN 1 MESH SELECTED"<< std::endl;
        return nullptr;
    }

    for(std::list<Resource*>::const_iterator item = resources.begin(); item != resources.end(); item++)
    {
        if(selected_items.at(0)->text() == (*item)->GetName())
            return (*item);
    }
}
