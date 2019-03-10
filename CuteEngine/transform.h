#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"
#include <QVector3D>
#include <qmatrix4x4.h>

class Transform : public Component
{
public:   

    explicit Transform(QWidget *aParent = nullptr);
    ~Transform()override;

private:

    QMatrix4x4 transform_matrix;
    QVector3D position;


};

#endif // TRANSFORM_H
