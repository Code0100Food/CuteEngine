#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "component.h"

class hdr_texture;
class QComboBox;
class QGridLayout;

class Environment : public QWidget
{
    Q_OBJECT

public:
    Environment(QWidget* parent = nullptr);
    ~Environment();

    void UpdateComboBox(int type, const char *name);

    void AddHDRTexture(const char *name);

    bool SkyBoxReady() const;
    unsigned int GetSkyboxTexture() const;
    unsigned int GetHDRTexture() const;

    hdr_texture* texture = nullptr;
    bool needs_processing = false;
    //TextureCube* environment_map = nullptr;

private:
    QGridLayout* layout = nullptr;
    QComboBox* select_texture_combo_box = nullptr;
    //GLTextureCube TextureCube;

public slots:
    void SetSelectedTexture(int value);

};

#endif // ENVIRONMENT_H
