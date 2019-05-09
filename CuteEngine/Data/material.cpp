#include "material.h"
#include "texture.h"
#include "iostream"
#include <QOpenGLFunctions>
#include "qt_application.h"
#include "mainwindow.h"
#include "resourcemanager.h"

//----------------------SubMaterial-------------------------------
SubMaterial::SubMaterial()
{

}

void SubMaterial::Reload()
{
    for(std::vector<std::string>::iterator i = texture_names.begin(); i != texture_names.end(); i++)
    {
        Texture* loaded_tex = (Texture*)customApp->main_window()->resource_manager()->GetResourceByName((*i), RESOURCE_TYPE::RESOURCE_TEXTURE);
        if(loaded_tex)
        {
            AddTexture(loaded_tex);
        }
        else std::cout<< "TEXTURE NULL: " << (*i)<< std::endl;
    }

    needs_reload = false;
}

void SubMaterial::AddTexture(Texture *new_texture)
{
    textures.push_back(new_texture);
}

void SubMaterial::AddTexture(std::string texture_name)
{
    texture_names.push_back(texture_name);
}

void SubMaterial::BindTextures() const
{
    QOpenGLFunctions* gl_functions = QOpenGLContext::currentContext()->functions();

    unsigned int i = 0;
    for(std::vector<Texture*>::const_iterator item = textures.begin();  item != textures.end(); item++)
    {
        if((*item) == nullptr)
         {
            std::cout<< "Texture is null" << std::endl;
            continue;
        }

        if((*item)->NeedsReload())
        {
            std::cout<< "Texture is no load" << std::endl;
            continue;
        }
        //std::cout<< "Binding Texture: " << (*item)->GetName() <<  std::endl;

        gl_functions->glActiveTexture(GL_TEXTURE0 + i);
        gl_functions->glBindTexture(GL_TEXTURE_2D, (*item)->GetIndex());
        i++;
   }
}

//------------------------Material--------------------------------
Material::Material() : Resource(RESOURCE_TYPE::RESOURCE_MATERIAL)
{

    SetReload(true);

}

void Material::Reload()
{
    bool ret = false;
    foreach(SubMaterial* sub_mat, mesh_materials)
    {
        if(sub_mat->NeedsReload())
            sub_mat->Reload();
    }

    SetReload(false);
}

void Material::Draw(int texture_index)
{
    if(texture_index >= mesh_materials.size())
        return;

    mesh_materials[texture_index]->BindTextures();

}

void Material::UnBind()
{
    glBindTexture(GL_TEXTURE_2D, 0);
}
