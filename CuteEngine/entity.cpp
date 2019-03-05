#include "entity.h"

Entity::Entity(int _id) : id(_id)
{
    char buffer[10];
    itoa(id, buffer, 10);
    name = "Entity_";
    name += buffer;
}

Entity::Entity(int _id, const std::string _name) : id(_id), name(_name)
{

}

Entity::Entity(const Entity& _entity) : id(_entity.id), name(_entity.name)
{

}

std::string Entity::GetName() const
{
    return name;
}
