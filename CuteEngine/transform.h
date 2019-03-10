#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"
#include <QVector3D>
#include <QMatrix4x4>
#include <QQuaternion>

class Transform : public Component
{
    Q_OBJECT

public:   

    explicit Transform(QWidget *aParent = nullptr);
    ~Transform()override;

private:

    QMatrix4x4 transform_matrix;

    QVector3D position;
    QVector3D rotation_euler_angles;
    QQuaternion rotation_quaternion;
    QVector3D scale;

    QMatrix4x4 inherited_transform;


public slots:

    void SetXPosition(double value);
    void SetYPosition(double value);
    void SetZPosition(double value);

};

#endif // TRANSFORM_H
