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
    void RemoveEntities();
    void RemoveEntity(std::string entity_to_remove);

    std::list<Entity*> GetSelectedEntities()const;
    const std::list<Entity*> GetEntities()const { return entities; }
    Entity* GetSelectedEntity()const;

    Entity* FindEntity(std::string entity_name);

    void SetSelectedEntity(std::string entity_name);
    void RenameSelectedEntity(std::string new_entity_name);

    void SetBackgroundColor(const QVector4D new_color);
    const QVector4D GetBackgroundColor()const;

private:

    std::list<Entity*> entities;
    Entity* selected_entity = nullptr;
    qt_Application* app = nullptr;
    QVector4D BackgroundColor;

};

#endif // MAINSCENE_H
