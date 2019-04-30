#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "component.h"
class Mesh;

class MeshRenderer : public Component
{
public:
    MeshRenderer();

    void Update() override;
    void Draw();

    Mesh* GetCurrentMesh() const { return current_mesh; }
private:
    Mesh* current_mesh = nullptr;


public slots:
    void SetSelectedMesh();

};

#endif // MESHRENDERER_H
