#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"

class Transform : public Component
{
public:   

    explicit Transform(QWidget *aParent = nullptr);
    ~Transform()override;
};

#endif // TRANSFORM_H
