#ifndef ENVIRONMENT_H
#define ENVIRONMENT_H

#include "component.h"

class Texture;

class Environment : public Component
{
public:
    Environment();

    void Update() override;

    void handleResourcesAboutToDie();

    void read(const QJsonObject& json);
    void write(QJsonObject& json);

    Texture* texture = nullptr;
    bool needsProcessing = false;

};

#endif // ENVIRONMENT_H
