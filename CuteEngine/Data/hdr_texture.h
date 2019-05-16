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

private:
    unsigned int id = 0;
    std::string filename;
    float* hdr_data;
};

#endif // HDR_TEXTURE_H
