#include "mesh.h"
#include "iostream"
#include "submesh.h"
Mesh::Mesh()
{

}

Mesh::~Mesh()
{
   for(std::vector<Submesh*>::iterator iter = meshes.begin(); iter != meshes.end(); iter++)
   {
       if((*iter) != nullptr)
           delete (*iter);
   }

   meshes.clear();
}

void Mesh::Reload()
{
    foreach (Submesh* submesh, meshes) {
        submesh->ReLoad();
    }
}

void Mesh::Draw()
{
    foreach (Submesh* submesh, meshes) {
        submesh->Draw();
    }
}

void Mesh::Destroy()
{
    foreach (Submesh* submesh, meshes) {
        submesh->Destroy();
    }
}

void Mesh::AddSubMesh(Submesh *new_mesh)
{
    if(new_mesh != nullptr)
        meshes.push_back(new_mesh);
    else std::cout<< "ERROR: NEW SUBMESH IS NULL"<<std::endl;
}
