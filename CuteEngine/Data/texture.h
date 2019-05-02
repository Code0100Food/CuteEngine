#ifndef TEXTURE_H
#define TEXTURE_H

#include "resourcemanager.h"

class Texture : public Resource
{
public:
    Texture(const char* image_path);
    ~Texture() override;

    void Reload() override;
    void Draw() override;
    void Destroy() override;

    unsigned int GetIndex() const { return id; }


private:
    unsigned int id = 0;

    std::string texture_path;
};

#endif // TEXTURE_H
