#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QWidget>
#include <list>

enum RESOURCE_TYPE
{
    RESOURCE_MESH = 0
};

class Resource
{
public:
    Resource(RESOURCE_TYPE _type) : type(_type) {}
    virtual ~Resource() {}

    virtual void Reload() {}
    virtual void Draw() {}
    virtual void Destroy(){}

    bool NeedsReload() const { return needs_reload; }
    void SetReload(bool reload) { needs_reload = reload; }

private:
    bool needs_reload = false;
    RESOURCE_TYPE type;

};

class ResourceManager : public QWidget
{
    Q_OBJECT

public:
    ResourceManager(QWidget* parent = nullptr);

    void DebugDraw() const;

    void UpdateResources();
    void Import(std::string path);
    void AddResource(const Resource* new_resource);

private:
    std::list<Resource*> resources;

    void ImportMesh(const char* path);
};

#endif // RESOURCEMANAGER_H
