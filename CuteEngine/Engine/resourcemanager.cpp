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
#include "environment.h"
#include "Data/texture.h"
#include "Data/material.h"
#include "Data/hdr_texture.h"

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
    LoadSkyboxQuad();

    //Load Materials
    //LoadPatrickMaterial();
    //LoadPalmeraMaterial();
}

void ResourceManager::Import(std::string path)
{
    std::cout << path.c_str() << std::endl;
    //Check file type
    std::string file_type = path.substr(path.find_last_of("."));
    std::cout << file_type.c_str() << std::endl;

    if(file_type == ".obj")
        ImportMesh(path);

    if(file_type == ".fbx")
        ImportMesh(path);

    if(file_type == ".png" || file_type == ".jpg" || file_type == ".JPG" || file_type == ".PNG")
        ImportTexture(path);

    if(file_type == ".hdr" || file_type == ".hdri")
        ImportHDRTexture(path);
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

    Material* mesh_material = new_mesh->GetMaterial();
    if(mesh_material)
    {
        resources.push_back(mesh_material);
        new_mesh->ResetMaterial();

        int start = path.find_last_of("/") + 1;
        int end = path.find_last_of(".");

        std::string name = path.substr(start, end-start).c_str();
        name += ".mtl";
        mesh_material->SetName(name.c_str());
        widget_resources_list->addItem(name.c_str());
    }

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

            if((*i)->GetType() == RESOURCE_TYPE::RESOURCE_MATERIAL && !(*i)->NeedsReload())
                 customApp->main_window()->inspector()->AddMaterialToWidget((*i)->GetName());

            if((*i)->GetType() == RESOURCE_TYPE::RESOURCE_HDR_TEXTURE && !(*i)->NeedsReload())
                 customApp->main_window()->environment()->AddHDRTexture((*i)->GetName());
        }
    }

    if(screen_quad->NeedsReload())
        screen_quad->Reload();

    if(skybox_quad->NeedsReload())
        skybox_quad->Reload();
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

void ResourceManager::LoadSkyboxQuad()
{
    // TODO: Rest of the faces
    float vertex_attributes[24] = {
        -1.0f, -1.0f, 1.0f,  //0
         1.0f, 1.0f,  1.0f,  //1
        -1.0f, 1.0f,  1.0f,  //2
         1.0f, -1.0f, 1.0f,  //3
        -1.0f, -1.0f, -1.0f, //4
         1.0f, 1.0f,  -1.0f, //5
        -1.0f, 1.0f,  -1.0f, //6
         1.0f, -1.0f, -1.0f, //7
    };

    unsigned int indices_backface[6] = { 4, 6, 5, 4, 5, 7 };

    unsigned int indices_rightface[6] = { 7, 5, 1, 7, 1, 3 };
    unsigned int indices_frontface[6] = { 1, 2, 0, 1, 0, 3 };
    unsigned int indices_leftface[6] = { 0, 2, 6, 0, 6, 4 };
    unsigned int indices_upface[6] = { 5, 6, 2, 5, 2, 1 };
    unsigned int indices_downface[6] = { 7, 3, 0, 7, 0, 4 };

    /*unsigned int indices_backface[6] = { 7,6,5,7,4,6 };

    unsigned int indices_rightface[6] = { 7, 5, 1, 7, 1, 3 };
    unsigned int indices_frontface[6] = { 3,1,2,3,2,0 };
    unsigned int indices_leftface[6] = { 2,6,4,2,4,0 };
    unsigned int indices_upface[6] = { 2,5,6,2,1,5 };
    unsigned int indices_downface[6] = {0,4,7,0,7,3 };*/

    VertexFormat format;
    format.SetVertexAttribute(0, 0, 3);

    skybox_quad = new Mesh();
    Submesh* tmp = new Submesh(format, &vertex_attributes[0], 24 * sizeof(float), &indices_backface[0],  6);
    Submesh* tmp_1 = new Submesh(format, &vertex_attributes[0], 24 * sizeof(float), &indices_rightface[0], 6);
    Submesh* tmp_2 = new Submesh(format, &vertex_attributes[0], 24 * sizeof(float), &indices_frontface[0], 6);
    Submesh* tmp_3 = new Submesh(format, &vertex_attributes[0], 24 * sizeof(float), &indices_leftface[0],  6);
    Submesh* tmp_4 = new Submesh(format, &vertex_attributes[0], 24 * sizeof(float), &indices_upface[0],    6);
    Submesh* tmp_5 = new Submesh(format, &vertex_attributes[0], 24 * sizeof(float), &indices_downface[0],  6);
    skybox_quad->AddSubMesh(tmp);
    skybox_quad->AddSubMesh(tmp_1);
    skybox_quad->AddSubMesh(tmp_2);
    skybox_quad->AddSubMesh(tmp_3);
    skybox_quad->AddSubMesh(tmp_4);
    skybox_quad->AddSubMesh(tmp_5);
    skybox_quad->SetReload(true);
}

Resource* ResourceManager::GetResourceByName(std::string name, RESOURCE_TYPE type)
{
    foreach(Resource* res, resources)
    {
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
   Texture* new_texture = new Texture(path.c_str(), TEXTURE_TYPE::ALBEDO);
   new_texture->SetName(path.substr(path.find_last_of("/") + 1).c_str());

   std::cout<< "Imported TEXTURE: " << new_texture->GetName() <<std::endl;

   //Add the new mesh to the resources list
   resources.push_back(new_texture);

   //Add the new mesh to the UI
   widget_resources_list->addItem(new_texture->GetName());
}

void ResourceManager::ImportHDRTexture(std::string path)
{
    std::cout << path << std::endl;

   hdr_texture* new_hdr_texture = new hdr_texture(path.c_str());
   new_hdr_texture->SetName(path.substr(path.find_last_of("/") + 1).c_str());

   std::cout<< "Imported HDR TEXTURE: " << new_hdr_texture->GetName() <<std::endl;

   //Add the new mesh to the resources list
   resources.push_back(new_hdr_texture);

   //Add the new mesh to the UI
   widget_resources_list->addItem(new_hdr_texture->GetName());
}

void ResourceManager::LoadPatrickMaterial()
{
    std::vector<Texture*> patrick_textures;
    Texture* colors = (Texture*)GetResourceByName("Color.png", RESOURCE_TYPE::RESOURCE_TEXTURE);

    patrick_textures.push_back(colors);
    patrick_textures.push_back(colors);
    patrick_textures.push_back(colors);
    patrick_textures.push_back((Texture*)GetResourceByName("Flowers.png", RESOURCE_TYPE::RESOURCE_TEXTURE));
    patrick_textures.push_back((Texture*)GetResourceByName("Skin_Patrick.png", RESOURCE_TYPE::RESOURCE_TEXTURE));
    patrick_textures.push_back(colors);

    std::vector<SubMaterial*> submaterials;


    SubMaterial* tmp = new SubMaterial();
    tmp->AddTexture("Color.png");

    Material* new_material = new Material();


    new_material->SetName("Patrick_Material.mtl");

    //Add the new mesh to the resources list
    resources.push_back(new_material);

    //Add the new mesh to the UI
    widget_resources_list->addItem(new_material->GetName());
}

void ResourceManager::LoadPalmeraMaterial()
{
 //  std::vector<Texture*> palmera_textures;
 //
 //  palmera_textures.push_back((Texture*)GetResourceByName("ENV_MP_Iraq_palm_tree_01_D.png", RESOURCE_TYPE::RESOURCE_TEXTURE));
 //  palmera_textures.push_back((Texture*)GetResourceByName("ENV_MP_Iraq_PlantsSansTrans_D.png", RESOURCE_TYPE::RESOURCE_TEXTURE));
 //
 //  Material* new_material = new Material(palmera_textures);
 //  new_material->SetName("PalmTree_Material.mtl");
 //
 //  //Add the new mesh to the resources list
 //  resources.push_back(new_material);
 //
 //  //Add the new mesh to the UI
 //  widget_resources_list->addItem(new_material->GetName());
}
