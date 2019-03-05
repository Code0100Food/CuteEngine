#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>

class Component;

class Entity
{
public:
    Entity(int _id);
    Entity(int _id, const std::string _name);
    Entity(const Entity& _entity);
    ~Entity(){}

private:
    int id;
    std::string name;
    std::vector<Component*> components;
};

#endif // ENTITY_H
