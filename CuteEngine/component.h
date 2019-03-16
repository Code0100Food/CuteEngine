#ifndef COMPONENT_H
#define COMPONENT_H

#include <QWidget>

class QVBoxLayout;

enum COMPONENT_TYPE
{
    UNDEFINED_COMPONENT = 0,
    COMPONENT_TRANSFORM,
    COMPONENT_PRIMITIVE
};

class Component : public QWidget
{
    Q_OBJECT

public:

    explicit Component(QWidget* parent = nullptr);
    ~Component() override;

protected:

    std::string name = "undef";
    COMPONENT_TYPE type = COMPONENT_TYPE::UNDEFINED_COMPONENT;

public:

    COMPONENT_TYPE GetType()const;

    virtual void GoToInspector(QVBoxLayout*){};
    virtual void ShowUI();
    virtual void HideUI();

};

#endif // COMPONENT_H
