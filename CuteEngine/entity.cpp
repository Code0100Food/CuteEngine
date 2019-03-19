#include "entity.h"
#include "component.h"

Entity::Entity(int _id) : id(_id)
{
    char buffer[10];
    _itoa_s(id, buffer, 10);
    name = "Entity_";
    name += buffer;
}

Entity::Entity(int _id, const std::string _name) : id(_id), name(_name)
{

}

Entity::Entity(const Entity& _entity) : id(_entity.id), name(_entity.name)
{

}

Entity::~Entity()
{
    size_t len = components.size();
    for(size_t k = 0; k < len; k++)
    {
        delete components[k];
    }
    components.clear();

    name.clear();
}

void Entity::Update()
{
    for(size_t i = 0; i < components.size(); i++)
    {
        components[i]->Update();
    }
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
    size_t len = components.size();
    for(size_t k = 0; k < len; k++)
    {
        if(components[k]->GetType() == target_type)
        {
            return components[k];
        }
    }
    return nullptr;
}

void Entity::Select()
{
    if(components.empty())return;

    size_t len = components.size();
    for(size_t k = 0; k < len; k++)
    {
        components[k]->ShowUI();
    }
}

void Entity::Deselect()
{
    if(components.empty())return;

    size_t len = components.size();
    for(size_t k = 0; k < len; k++)
    {
        components[k]->HideUI();
    }
}
