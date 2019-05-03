#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>
#include "resourcemanager.h"

class Texture;
class QVector4D;

class SubMaterial
{
public:
    SubMaterial();

    void AddTexture(Texture* new_texture);
    void BindTextures() const;

private:
    std::vector<Texture*> textures;
};



class Material : public Resource
{
public:
    Material(const std::vector<Texture*>& textures);

    void Reload() override;
    void Draw(int texture_index);

private:
    std::vector<SubMaterial*> mesh_materials;
};

#endif // MATERIAL_H
