#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "component.h"

class Texture;
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
    void SetSelectedTexture(int value);

    Texture* texture = nullptr;
    bool needs_processing = false;
    //TextureCube* environment_map = nullptr;

private:
    QGridLayout* layout = nullptr;
    QComboBox* select_texture_combo_box = nullptr;
    //GLTextureCube TextureCube;

};

#endif // ENVIRONMENT_H
