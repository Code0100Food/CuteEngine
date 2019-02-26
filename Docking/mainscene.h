#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <iostream>
#include <vector>

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

    int id;
    std::string name;
};

class MainScene
{
public:
    MainScene();

    void SetApp(qt_Application& _app);
    std::vector<Entity*> entities;

private:
    qt_Application* app = nullptr;

};

#endif // MAINSCENE_H
