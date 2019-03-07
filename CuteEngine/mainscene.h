#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <iostream>
#include <vector>
#include <list>

class qt_Application;
class Entity;

class MainScene
{
public:

    MainScene();
    ~MainScene();

public:

    void AddEntity(Entity* new_entity);
    void RemoveEntities();
    void RemoveEntity(std::string entity_to_remove);
    std::list<Entity*> GetSelectedEntities()const;

    void SetSelectedEntity(std::string entity_name);
    void RenameSelectedEntity(std::string new_entity_name);
private:

    std::list<Entity*> entities;
    Entity* selected_entity = nullptr;
    qt_Application* app = nullptr;

    Entity* FindEntity(std::string entity_name);

};

#endif // MAINSCENE_H
