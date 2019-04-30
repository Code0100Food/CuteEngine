#ifndef TEXTURE_H
#define TEXTURE_H

#include "resourcemanager.h"

class Texture : public Resource
{
public:
    Texture(unsigned char* buffer, int _width, int _height);
    ~Texture() override;

    void Reload() override;
    void Draw() override;
    void Destroy() override;

    unsigned int GetIndex() const { return id; }

private:
    unsigned int id = 0;

    int width = 0;
    int height = 0;
    unsigned char* image_data = nullptr;
};

#endif // TEXTURE_H
