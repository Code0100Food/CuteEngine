#include "entity.h"
#include "component.h"

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

void Entity::AddComponent(Component* new_component)
{
    components.push_back(new_component);
}

Component* Entity::FindComponent(COMPONENT_TYPE target_type)const
{
    //TODO
    return nullptr;
}