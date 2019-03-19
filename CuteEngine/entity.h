#ifndef ENTITY_H
#define ENTITY_H

#include <string>
#include <vector>

class Component;
enum COMPONENT_TYPE;

class Entity
{
public:
    Entity(int _id);
    Entity(int _id, const std::string _name);
    Entity(const Entity& _entity);
    ~Entity();

    void Update();

private:

    int id;
    std::string name;
    std::vector<Component*> components;

public:

    std::string GetName()const;
    void SetName(std::string new_entity_name) { name = new_entity_name; }

    void AddComponent(Component* new_component);
    Component* FindComponent(COMPONENT_TYPE target_type)const;

    void Select();
    void Deselect();
};

#endif // ENTITY_H
