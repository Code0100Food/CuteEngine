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

    void AddEntity(Entity* new_entity);
    void RemoveEntities();
    void RemoveEntity(std::string entity_to_remove);

private:
    std::list<Entity*> entities;
    qt_Application* app = nullptr;

};

#endif // MAINSCENE_H
