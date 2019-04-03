#ifndef MESH_H
#define MESH_H

#include <vector>
#include <queue>

class Submesh;
struct aiNode;
struct aiScene;
struct aiMesh;

class Mesh
{
public:
    Mesh();
    ~Mesh();

    void Reload();
    void Draw();
    void Destroy();

    void AddSubMesh(Submesh* new_mesh);
    bool NeedsReload() const { return needs_reload; }

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
