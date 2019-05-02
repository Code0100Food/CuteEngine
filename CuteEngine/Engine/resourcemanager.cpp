#include "resourcemanager.h"
#include "iostream"
#include "../Data/mesh.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myopenglwidget.h"
#include "qt_application.h"
#include <QListWidget>
#include <QLabel>
#include <QDir>
#include <QDirIterator>
#include "Data/mesh.h"
#include "Data/submesh.h"
#include "inspector.h"
#include "Data/texture.h"

ResourceManager::ResourceManager(QWidget* parent) : QWidget(parent)
{
    widget_resources_list = new QListWidget(parent);

    QVBoxLayout* _layout = new QVBoxLayout();
    _layout->addWidget(widget_resources_list);

    setLayout(_layout);

    //Init Load All resources
    QString resources_path = customApp->applicationDirPath() + "/Resources";
    std::cout<<resources_path.toStdString()<<std::endl;
    QDir resources_dir(resources_path);

    QDirIterator resources_searcher(resources_dir, QDirIterator::Subdirectories);

    while(resources_searcher.hasNext())
    {
        if(resources_searcher.fileInfo().suffix() != "")
            Import(resources_searcher.filePath().toStdString());

        resources_searcher.next();
    }

    //Load the screen
    LoadScreenQuad();
}

void ResourceManager::Import(std::string path)
{
    //Check file type
    std::string file_type = path.substr(path.find_last_of("."));

    if(file_type == ".obj")
        ImportMesh(path);

    if(file_type == ".png")
        ImportTexture(path);
}

void ResourceManager::ImportMesh(std::string path)
{
    Mesh* new_mesh = new Mesh();
    new_mesh->SetName(path.substr(path.find_last_of("/") + 1).c_str());
    new_mesh->LoadModel(path.c_str());    
    std::cout<< "LOADED MESH: " << new_mesh->GetName() <<std::endl;

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

            if((*i)->GetType() == RESOURCE_TYPE::RESOURCE_MESH)
                customApp->main_window()->inspector()->AddMeshToWidget((*i)->GetName());

             if((*i)->GetType() == RESOURCE_TYPE::RESOURCE_TEXTURE)
                  customApp->main_window()->inspector()->AddtextureToWidget((*i)->GetName());
        }


    }

    if(screen_quad->NeedsReload())
        screen_quad->Reload();

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
        if((*item)->GetType() == RESOURCE_TYPE::RESOURCE_MESH && selected_items.at(0)->text() == (*item)->GetName())
            return (*item);
    }
}

void ResourceManager::LoadScreenQuad()
{
    float vertex_attributes[20] = {
        -1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 0.0f, 1.0f, 1.0f,
        -1.0f, 1.0f, 0.0f, 0.0f, 1.0f,
        1.0f, -1.0f, 0.0f, 1.0f, 0.0f
    };

    unsigned int indices[6] = {
      0, 1, 2,
      0, 3, 1
    };

    VertexFormat format;
    format.SetVertexAttribute(0, 0, 3);
    format.SetVertexAttribute(1, 3 * sizeof(float), 2);

    screen_quad = new Mesh();
    Submesh* tmp = new Submesh(format, &vertex_attributes[0], 20 * sizeof(float), &indices[0], 6);
    screen_quad->AddSubMesh(tmp);
    screen_quad->SetReload(true);
}

Resource* ResourceManager::GetResourceByName(std::string name, RESOURCE_TYPE type)
{
    std::cout<< "Num resource: " << resources.size() << std::endl;

    foreach(Resource* res, resources)
    {
        std::cout<< "resource: " << res->GetName()<< std::endl;
        std::cout<< "resource type: " << res->GetType()<< std::endl;

        if(res->GetType() == type && name == res->GetName())
        {
            std::cout<< "Returned resource: " << res->GetName()<< std::endl;
            return res;
        }
    }

    return nullptr;
}

void ResourceManager::ImportTexture(std::string path)
{
   Texture* new_texture = new Texture(path.c_str());
   new_texture->SetName(path.substr(path.find_last_of("/") + 1).c_str());

   std::cout<< "LOADED TEXTURE: " << new_texture->GetName() <<std::endl;

   //Add the new mesh to the resources list
   resources.push_back(new_texture);

   //Add the new mesh to the UI
   widget_resources_list->addItem(new_texture->GetName());
}
