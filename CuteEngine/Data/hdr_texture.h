#ifndef HDR_TEXTURE_H
#define HDR_TEXTURE_H

#include "resourcemanager.h"

class hdr_texture : public Resource
{
public:
    hdr_texture(const char* image_path);

    void Reload() override;
    void Draw() override;
    void Destroy() override;

    unsigned int GetHDRTexture() const { return hdr_id; }
    unsigned int GetCubeMapexture() const { return cubemap_id; }

    int GetCubeMapSize() const { return width/4; }

private:
    unsigned int hdr_id = 0;
    unsigned int cubemap_id = 0;

    std::string filename;
    float* hdr_data;

    int width = 0;
    int height = 0;
};

#endif // HDR_TEXTURE_H
