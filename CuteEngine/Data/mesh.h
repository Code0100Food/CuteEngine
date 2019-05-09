#ifndef MESH_H
#define MESH_H

#include <vector>
#include <queue>
#include "resourcemanager.h"

class Submesh;
struct aiNode;
struct aiScene;
struct aiMesh;
class Material;

class Mesh : public Resource
{
public:
    Mesh();
    ~Mesh() override;

    void Reload() override;
    void Draw(Material* material);
    void Draw() override;
    void Destroy() override;

    void AddSubMesh(Submesh* new_mesh);

    void LoadModel(const char* path);
    std::vector<Submesh*> meshes;

    unsigned int debug = 0;

    Material* GetMaterial() const { return mesh_mat; }
    void ResetMaterial() { mesh_mat = nullptr; }

private:
    //Load Stuff
    std::queue<aiNode*> nodes;
    void ProcessNodes(const aiScene* scene);
    void ProcessNode(aiNode* node, const aiScene* scene);
    Submesh* ProcessSubMesh(aiMesh* mesh, const aiScene* scene);

    Material* mesh_mat = nullptr;
};

#endif // MESH_H
