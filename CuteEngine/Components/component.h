#ifndef COMPONENT_H
#define COMPONENT_H

#include <QWidget>

class QVBoxLayout;

enum COMPONENT_TYPE
{
    UNDEFINED_COMPONENT = 0,
    COMPONENT_TRANSFORM,
    COMPONENT_MESHRENDERER,
    COMPONENT_PRIMITIVE
};

class Component
{

public:

    explicit Component();
    virtual ~Component();

    virtual void Update();

protected:

    std::string name = "undef";
    COMPONENT_TYPE type = COMPONENT_TYPE::UNDEFINED_COMPONENT;

public:

    COMPONENT_TYPE GetType()const;
};

#endif // COMPONENT_H
