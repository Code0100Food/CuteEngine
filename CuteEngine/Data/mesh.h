#ifndef MESH_H
#define MESH_H

#include <vector>
#include <queue>
#include "resourcemanager.h"

class Submesh;
struct aiNode;
struct aiScene;
struct aiMesh;

class Mesh : public Resource
{
public:
    Mesh();
    ~Mesh() override;

    void Reload() override;
    void Draw();
    void Destroy() override;

    void AddSubMesh(Submesh* new_mesh);

    void LoadModel(const char* path);
    std::vector<Submesh*> meshes;

private:

    bool needs_reload = false;

    //Load Stuff
    std::queue<aiNode*> nodes;
    void ProcessNode(aiNode* node, const aiScene* scene);
    Submesh* ProcessSubMesh(aiMesh* mesh, const aiScene* scene);
};

#endif // MESH_H
