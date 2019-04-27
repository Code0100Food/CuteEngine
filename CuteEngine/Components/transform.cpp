#include "transform.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>

Transform::Transform() : Component()
{
    type = COMPONENT_TYPE::COMPONENT_TRANSFORM;

    //Data initialization
    transform_matrix.setToIdentity();
}

Transform::~Transform()
{

}

void Transform::Update()
{
    if(!needs_update) return;

    transform_matrix.setToIdentity();

    std::cout<< "Euler Angles: x: " << rotation_euler_angles.x() << " y: " << rotation_euler_angles.y() << " z: "<< rotation_euler_angles.z() <<std::endl;

    transform_matrix.translate(position);
    transform_matrix.rotate(rotation_euler_angles.x(), QVector3D(1.0f, 0.0f, 0.0f));
    transform_matrix.rotate(rotation_euler_angles.y(), QVector3D(0.0f, 1.0f, 0.0f));
    transform_matrix.rotate(rotation_euler_angles.z(), QVector3D(0.0f, 0.0f, 1.0f));
    transform_matrix.scale(scale);

    needs_update = false;
}

void Transform::SetXPosition(double value)
{
    position.setX(static_cast<float>(value));
    needs_update = true;
}

void Transform::SetYPosition(double value)
{
    position.setY(static_cast<float>(value));
    needs_update = true;
}

void Transform::SetZPosition(double value)
{
    position.setZ(static_cast<float>(value));
    needs_update = true;
}

void Transform::SetXRotation(double value)
{
    rotation_euler_angles.setX(static_cast<float>(value));
    rotation_quaternion.fromEulerAngles(rotation_euler_angles);

    needs_update = true;
}

void Transform::SetYRotation(double value)
{
    rotation_euler_angles.setY(static_cast<float>(value));
    rotation_quaternion.fromEulerAngles(rotation_euler_angles);

    needs_update = true;
}

void Transform::SetZRotation(double value)
{
    rotation_euler_angles.setZ(static_cast<float>(value));
    rotation_quaternion.fromEulerAngles(rotation_euler_angles);

    needs_update = true;
}

void Transform::SetXScale(double value)
{
    scale.setX(static_cast<float>(value));
    needs_update = true;
}

void Transform::SetYScale(double value)
{
    scale.setY(static_cast<float>(value));
    needs_update = true;
}

void Transform::SetZScale(double value)
{
    scale.setZ(static_cast<float>(value));
    needs_update = true;
}
