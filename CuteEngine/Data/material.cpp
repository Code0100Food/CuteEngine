#include "material.h"
#include "texture.h"
#include "iostream"
#include <QOpenGLFunctions>

//----------------------SubMaterial-------------------------------
SubMaterial::SubMaterial()
{

}

void SubMaterial::AddTexture(Texture *new_texture)
{
    textures.push_back(new_texture);
}

void SubMaterial::BindTextures() const
{
    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();

    unsigned int i = 0;
    for(std::vector<Texture*>::const_iterator item = textures.begin();  item != textures.end(); item++)
    {
        if((*item) == nullptr || (*item)->NeedsReload())
            continue;

        gl_functions->glActiveTexture(GL_TEXTURE0 + i);
        gl_functions->glBindTexture(GL_TEXTURE_2D, (*item)->GetIndex());
        i++;
   }
}

//------------------------Material--------------------------------
Material::Material(const std::vector<Texture*>& textures) : Resource(RESOURCE_TYPE::RESOURCE_MATERIAL)
{

    for(unsigned int i = 0; i < textures.size(); i++)
    {
        SubMaterial* new_sub_material = new SubMaterial();
        new_sub_material->AddTexture(textures[i]);

        mesh_materials.push_back(new_sub_material);
    }

    SetReload(true);

}

void Material::Reload()
{
    SetReload(false);
}

void Material::Draw(int texture_index)
{
    if(texture_index >= mesh_materials.size())
        return;

    mesh_materials[texture_index]->BindTextures();
}
