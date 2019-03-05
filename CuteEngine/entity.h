#ifndef ENTITY_H
#define ENTITY_H

#include <string>

class Entity
{
public:
    Entity(int _id);
    Entity(int _id, const std::string _name);
    Entity(const Entity& _entity);
    ~Entity(){}

    std::string GetName()const;

private:
    int id;
    std::string name;
};

#endif // ENTITY_H
