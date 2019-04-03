#include "resourcemanager.h"
#include "../Data/mesh.h"

ResourceManager::ResourceManager(QWidget* parent) : QWidget(parent)
{

}

void ResourceManager::ImportMesh(const char *path)
{
    Mesh* new_mesh = new Mesh();
    new_mesh->LoadModel(path);

    resources.push_back(new_mesh);
}
