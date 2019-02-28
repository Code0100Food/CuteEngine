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
    void RemoveEntities(std::list<std::string> entities_to_remove);

    void SetApp(qt_Application *_app);

private:
    std::list<Entity*> entities;
    qt_Application* app = nullptr;

};

#endif // MAINSCENE_H
