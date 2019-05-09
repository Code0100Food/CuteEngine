#ifndef TEXTURE_H
#define TEXTURE_H

#include "resourcemanager.h"

enum TEXTURE_TYPE
{
    ALBEDO = 0,
    NORMAL_MAP
};


class Texture : public Resource
{
public:
    Texture(const char* image_path, TEXTURE_TYPE text_type);
    ~Texture() override;

    void Reload() override;
    void Draw() override;
    void Destroy() override;

    unsigned int GetIndex() const { return id; }
    TEXTURE_TYPE GetTextureType() const { return texture_type; }

private:
    unsigned int id = 0;

    TEXTURE_TYPE texture_type = ALBEDO;
    std::string texture_path;
};

#endif // TEXTURE_H
