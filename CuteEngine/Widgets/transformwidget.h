#ifndef TRANSFORMWIDGET_H
#define TRANSFORMWIDGET_H

#include <QWidget>
class QDoubleSpinBox;
class Entity;
class Transform;

class TransformWidget : public QWidget
{
    Q_OBJECT

public:
    TransformWidget(QWidget* parent);


    void GetEntityValues(QVector3D position, QVector3D rotation, QVector3D scale);
    void ModifyEntityValues(Entity* selected_entity);

    void SetSelectedTransform(Transform* entity_transform) { selcted_entity_transform = entity_transform;}
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

    Transform* selcted_entity_transform = nullptr;

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

#endif // TRANSFORMWIDGET_H
