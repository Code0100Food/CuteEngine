#ifndef MATERIAL_H
#define MATERIAL_H

#include <vector>
#include "resourcemanager.h"
#include <map>

class Texture;
class QVector4D;

class SubMaterial
{
public:
    SubMaterial();

    void Reload();

    void AddTexture(std::string texture_name);
    void BindTextures() const;

    bool NeedsReload() const { return needs_reload; }
private:

    std::vector<Texture*> textures;
    std::vector<std::string> texture_names;

    void AddTexture(Texture* new_texture);
    bool needs_reload = true;
};



class Material : public Resource
{
public:
    Material();

    void Reload() override;
    void Draw(int texture_index);
    void UnBind();

    void AddSubMaterial(SubMaterial* new_submaterial) { mesh_materials.push_back(new_submaterial); }

    unsigned int GetNumSubMaterials() const { return mesh_materials.size(); }
private:
    std::vector<SubMaterial*> mesh_materials;
};

#endif // MATERIAL_H
