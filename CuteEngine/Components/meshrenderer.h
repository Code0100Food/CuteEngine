#ifndef MESHRENDERER_H
#define MESHRENDERER_H

#include "component.h"

class QLabel;
class Mesh;

class MeshRenderer : public Component
{
    Q_OBJECT
public:
    MeshRenderer();

    void Update() override;
    void Draw();

private:
    Mesh* current_mesh = nullptr;
    QLabel* select_mesh = nullptr;

public slots:
    void SetSelectedMesh();

};

#endif // MESHRENDERER_H
