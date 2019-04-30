#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"
#include <QVector3D>
#include <QMatrix4x4>
#include <QQuaternion>

class Transform : public Component
{


public:   

    explicit Transform();
    ~Transform() override;

    void Update() override;

private:
    QMatrix4x4 transform_matrix;

    QVector3D position;
    QVector3D rotation_euler_angles = QVector3D(0.0f,0.0f,0.0f);
    QQuaternion rotation_quaternion;
    QVector3D scale = QVector3D(1.0f,1.0f,1.0f);

    QMatrix4x4 inherited_transform;
    bool needs_update = false;

public:

    const QMatrix4x4* GetLocalTransform()const {return &transform_matrix;}

    QVector3D GetPosition()const { return position; }
    QVector3D GetRotation()const { return rotation_euler_angles; }
    QVector3D GetScale()const { return scale; }

    void SetXPosition(double value);
    void SetYPosition(double value);
    void SetZPosition(double value);
    void SetXRotation(double value);
    void SetYRotation(double value);
    void SetZRotation(double value);
    void SetXScale(double value);
    void SetYScale(double value);
    void SetZScale(double value);

};

#endif // TRANSFORM_H
