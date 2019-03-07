#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"

class Transform : public Component
{
public:   

    explicit Transform(QWidget *aParent = nullptr);

    void paintEvent(QPaintEvent* aEvent) override;

};

#endif // TRANSFORM_H
