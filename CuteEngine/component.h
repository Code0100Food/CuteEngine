#ifndef COMPONENT_H
#define COMPONENT_H

#include <QWidget>

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
    ~Component();

public:

    void paintEvent(QPaintEvent* aEvent) override;

protected:

    std::string name = "undef";
    COMPONENT_TYPE type = COMPONENT_TYPE::UNDEFINED_COMPONENT;

public:

    void ShowUI();
    void HideUI();

};

#endif // COMPONENT_H
