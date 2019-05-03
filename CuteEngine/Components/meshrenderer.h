#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "component.h"
class Mesh;
class Material;

class MeshRenderer : public Component
{
public:
    MeshRenderer();

    void Update() override;
    void Draw();

    Mesh* GetCurrentMesh() const { return current_mesh; }
    Material* GetCurrentMaterial()const { return mesh_material; }

    void SetCurrentMesh(Mesh* new_mesh) { current_mesh = new_mesh; }
    void SetCurrentMaterial(Material* new_material) { mesh_material = new_material; }


private:
    Mesh* current_mesh = nullptr;
    Material* mesh_material = nullptr;

};

#endif // MESHRENDERER_H
