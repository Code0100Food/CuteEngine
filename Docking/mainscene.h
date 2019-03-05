#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <iostream>
#include <vector>
#include <list>

class qt_Application;

class Entity
{
   public:
    Entity(int _id):id(_id)
    {
        char buffer[10];
        itoa(_id, buffer, 10);
        name = "Entity_";
        name += buffer;
    }
    Entity(const Entity& other_entity) {}
    ~Entity(){}

    int id;
    std::string name;
};

class MainScene
{
public:
    MainScene();
    ~MainScene();

    void AddEntity(Entity* new_entity);
    void RemoveEntities();
    void RemoveEntity(std::string entities_to_remove);

    void SetApp(qt_Application *_app);

private:
    std::list<Entity*> entities;
    qt_Application* app = nullptr;

};

#endif // MAINSCENE_H
