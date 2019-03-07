#ifndef COMPONENT_H
#define COMPONENT_H

#include <QWidget>

class Component : public QWidget
{
    Q_OBJECT

public:

    explicit Component(QWidget* parent = nullptr);
    ~Component();

    void paintEvent(QPaintEvent* aEvent) override;

private:

    std::string name = "undef";



public:
};

#endif // COMPONENT_H
