#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include <QWidget>
#include <list>
#include <map>

class QListWidget;
class Mesh;

enum RESOURCE_TYPE
{
    RESOURCE_MESH = 0,
    RESOURCE_TEXTURE
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

    void SetName(const char* _name){ name = _name; }
    const char* GetName() const { return name.c_str(); }

    RESOURCE_TYPE GetType() const { return type; }
private:

    std::string name;
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

    Resource* GetSelectedMesh() const;
    Mesh* ScreenQuad() const { return screen_quad; }

    //New Functionality
    Resource* GetResourceByName(std::string name, RESOURCE_TYPE type);


private:
    Mesh* screen_quad = nullptr;
    std::list<Resource*> resources;
    QListWidget* widget_resources_list = nullptr;

    void ImportMesh(std::string path);
    void ImportTexture(std::string path);
    void LoadScreenQuad();

    //UI

};

#endif // RESOURCEMANAGER_H
