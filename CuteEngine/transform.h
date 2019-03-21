#ifndef TRANSFORM_H
#define TRANSFORM_H

#include "component.h"
#include <QVector3D>
#include <QMatrix4x4>
#include <QQuaternion>

class QDoubleSpinBox;

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

private:

    QDoubleSpinBox* position_x = nullptr;
    QDoubleSpinBox* position_y = nullptr;
    QDoubleSpinBox* position_z = nullptr;
    QDoubleSpinBox* rotation_x = nullptr;
    QDoubleSpinBox* rotation_y = nullptr;
    QDoubleSpinBox* rotation_z = nullptr;
    QDoubleSpinBox* scale_x = nullptr;
    QDoubleSpinBox* scale_y = nullptr;
    QDoubleSpinBox* scale_z = nullptr;

public:

    const QDoubleSpinBox* GetPositionXButton() const { return position_x;}
    const QDoubleSpinBox* GetPositionYButton() const { return position_y;}
    const QDoubleSpinBox* GetPositionZButton(){ return position_z;}

    const QDoubleSpinBox* GetRotationXButton(){ return rotation_x;}
    const QDoubleSpinBox* GetRotationYButton(){ return rotation_y;}
    const QDoubleSpinBox* GetRotationZButton(){ return rotation_z;}

    const QDoubleSpinBox* GetScaleXButton() const { return scale_x;}
    const QDoubleSpinBox* GetScaleYButton() const { return scale_y;}
    const QDoubleSpinBox* GetScaleZButton(){ return scale_z;}

    const QVector3D* GetPosition(){ return &position; }
    const QVector3D* GetRotation(){ return &rotation_euler_angles; }
    const QVector3D* GetScale(){ return &scale; }

public slots:

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
