#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <iostream>
#include <vector>
#include <list>
#include <QVector4D>

class qt_Application;
class Entity;

class MainScene
{
public:

    MainScene();
    ~MainScene();

public:

    void Update();
    void Draw();

    void AddEntity(Entity* new_entity);
    void AddLight(Entity* new_light) { lights.push_back(new_light); }
    void RemoveEntities();
    void RemoveEntity(std::string entity_to_remove);

    std::list<Entity*> GetSelectedEntities()const;
    const std::list<Entity*> GetEntities()const { return entities; }
    const std::list<Entity*> GetLights()const { return lights; }
    Entity* GetSelectedEntity()const;

    Entity* FindEntity(std::string entity_name);

    void SetSelectedEntity(std::string entity_name);
    void RenameSelectedEntity(std::string new_entity_name);

    void SetBackgroundColor(const QVector4D new_color);
    const QVector4D GetBackgroundColor()const;

    bool IsGridPrint()const;
    void SetGridPrint(bool _print_grid);

private:

    std::list<Entity*> lights;
    std::list<Entity*> entities;
    Entity* selected_entity = nullptr;
    qt_Application* app = nullptr;
    QVector4D BackgroundColor;
    bool print_grid = true;

};

#endif // MAINSCENE_H
