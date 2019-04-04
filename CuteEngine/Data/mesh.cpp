#include "mesh.h"
#include "iostream"
#include "submesh.h"
#include "assimp/Importer.hpp"
#include "assimp/mesh.h"
#include "assimp/postprocess.h"
#include "assimp/scene.h"
#include <QFile>
#include <QIODevice>

Mesh::Mesh() : Resource(RESOURCE_MESH)
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
   foreach (Submesh* submesh, meshes)
       submesh->ReLoad();

   SetReload(false);
}

void Mesh::Draw()
{
    foreach (Submesh* submesh, meshes)
        submesh->Draw();
}

void Mesh::Destroy()
{
    foreach (Submesh* submesh, meshes) {
        submesh->Destroy();
    }
}

void Mesh::LoadModel(const char *path)
{
    Assimp::Importer importer;

    QFile file(path);
    if(file.open(QIODevice::ReadOnly) == false)
    {
        std::cout<< "Could not open file: "<< path << std::endl;
        return;
    }

    QByteArray data = file.readAll();

    const aiScene* scene = importer.ReadFileFromMemory(data.data(), (unsigned int)data.size(),
                                                       aiProcess_Triangulate |
                                                       aiProcess_FlipUVs |
                                                       aiProcess_GenSmoothNormals |
                                                       aiProcess_PreTransformVertices |
                                                       aiProcess_ImproveCacheLocality, ".obj");

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode )
    {
        std::cout<< "ASSIMP ERROR: "<< importer.GetErrorString() << std::endl;
        return;
    }

    //Read all nodes iterative
    nodes.push(scene->mRootNode);
    while(!nodes.empty())
    {
        ProcessNode(nodes.front(), scene);

        for(unsigned int i = 0; i < nodes.front()->mNumChildren; i++)
            nodes.push(nodes.front()->mChildren[i]);

        nodes.pop();
    }

   SetReload(true);
}

void Mesh::ProcessNode(aiNode *node, const aiScene *scene)
{
    //Check all meshes in this node
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        aiMesh* assimp_mesh = scene->mMeshes[node->mMeshes[i]];
        AddSubMesh(ProcessSubMesh(assimp_mesh, scene));
    }

}

Submesh* Mesh::ProcessSubMesh(aiMesh *mesh, const aiScene *scene)
{
    Submesh* ret = nullptr;

    std::vector<float> vertices;
    std::vector<unsigned int> indices;

    bool has_text_coords = false;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        //Process Vertices
        vertices.push_back(mesh->mVertices[i].x);
        vertices.push_back(mesh->mVertices[i].y);
        vertices.push_back(mesh->mVertices[i].z);

        //Process Normals
        vertices.push_back(mesh->mNormals[i].x);
        vertices.push_back(mesh->mNormals[i].y);
        vertices.push_back(mesh->mNormals[i].z);

        //Process Text Coords
        if(mesh->mTextureCoords[0])
        {
            has_text_coords = true;
            vertices.push_back(mesh->mTextureCoords[0][i].x);
            vertices.push_back(mesh->mTextureCoords[0][i].y);
        }
    }

    //Process Indices
    for(unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];

        for(unsigned int j = 0; j < face.mNumIndices; j++)
            indices.push_back(face.mIndices[j]);
    }

    VertexFormat format;
    format.SetVertexAttribute(0, 0, 3);
    format.SetVertexAttribute(1, 3 * sizeof(float), 3);

    if(has_text_coords)
        format.SetVertexAttribute(2, 6 * sizeof(float), 2);

    ret = new Submesh(format, &vertices[0], vertices.size() * sizeof(float), &indices[0], indices.size());

    return ret;
}

void Mesh::AddSubMesh(Submesh *new_mesh)
{
    if(new_mesh != nullptr)
        meshes.push_back(new_mesh);
    else std::cout<< "ERROR: NEW SUBMESH IS NULL"<<std::endl;
}
