#include "resourcemanager.h"
#include "iostream"
#include "../Data/mesh.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "myopenglwidget.h"
#include "qt_application.h"

ResourceManager::ResourceManager(QWidget* parent) : QWidget(parent)
{

}

void ResourceManager::Import(std::string path)
{
    //Check file type
    if(path.substr(path.find_last_of(".")) == ".obj")
        ImportMesh(path.c_str());

}



void ResourceManager::ImportMesh(const char *path)
{
    Mesh* new_mesh = new Mesh();
    new_mesh->LoadModel(path);

    resources.push_back(new_mesh);

}

void ResourceManager::DebugDraw() const
{
    int a = 0;
    for(std::list<Resource*>::const_iterator i = resources.begin(); i != resources.end(); i++)
    {
        if(!(*i)->NeedsReload())
         {
            std::cout<<"Draw Resource " << a << std::endl;
            (*i)->Draw();
        }
        a++;
    }
}

void ResourceManager::UpdateResources()
{
    int a = 0;
    for(std::list<Resource*>::const_iterator i = resources.begin(); i != resources.end(); i++)
    {
        if((*i)->NeedsReload())
        {
            std::cout<<"Update Resource " << a << std::endl;
            customApp->main_window()->uiMain()->openGLWidget->makeCurrent();
            (*i)->Reload();
        }

        a++;
    }
}
