#include "transformwidget.h"
#include <QLabel>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QVector3D>
#include "transform.h"

TransformWidget::TransformWidget(QWidget* parent) : QWidget(parent)
{
    //UI initialization
    QVBoxLayout* main_layout = new QVBoxLayout();

    //Window title
    QLabel* title = new QLabel("Transform");
    main_layout->addWidget(title);

    //Grid
    QGridLayout* grid = new QGridLayout();

    //Labels
    QLabel* position_label = new QLabel("Position");
    QLabel* rotation_label = new QLabel("Rotation");
    QLabel* scale_label = new QLabel("Scale");
    QLabel* position_label_x = new QLabel("X");
    QLabel* position_label_y = new QLabel("Y");
    QLabel* position_label_z = new QLabel("Z");
    QLabel* rotation_label_x = new QLabel("X");
    QLabel* rotation_label_y = new QLabel("Y");
    QLabel* rotation_label_z = new QLabel("Z");
    QLabel* scale_label_x = new QLabel("X");
    QLabel* scale_label_y = new QLabel("Y");
    QLabel* scale_label_z = new QLabel("Z");

    //Spin boxes
    position_x = new QDoubleSpinBox();
    position_x->setRange(-1000.0f,1000.0f);
    position_y = new QDoubleSpinBox();
    position_y->setRange(-1000.0f,1000.0f);
    position_z = new QDoubleSpinBox();
    position_z->setRange(-1000.0f,1000.0f);

    rotation_x = new QDoubleSpinBox();
    rotation_x->setRange(-360.0f,360.0f);
    rotation_y = new QDoubleSpinBox();
    rotation_y->setRange(-360.0f,360.0f);
    rotation_z = new QDoubleSpinBox();
    rotation_z->setRange(-360.0f,360.0f);

    scale_x = new QDoubleSpinBox();
    scale_x->setRange(0.0f,1000.0f);
    scale_y = new QDoubleSpinBox();
    scale_y->setRange(0.0f,1000.0f);
    scale_z = new QDoubleSpinBox();
    scale_z->setRange(0.0f,1000.0f);

    //Position
    grid->addWidget(position_label,0,0);
    grid->addWidget(position_label_x,0,1);
    grid->addWidget(position_x,0,2);
    grid->addWidget(position_label_y,0,3);
    grid->addWidget(position_y,0,4);
    grid->addWidget(position_label_z,0,5);
    grid->addWidget(position_z,0,6);

    //Position connections
    connect(position_x,SIGNAL(valueChanged(double)),this,SLOT(SetXPosition(double)));
    connect(position_y,SIGNAL(valueChanged(double)),this,SLOT(SetYPosition(double)));
    connect(position_z,SIGNAL(valueChanged(double)),this,SLOT(SetZPosition(double)));

    //Rotation
    grid->addWidget(rotation_label,1,0);
    grid->addWidget(rotation_label_x,1,1);
    grid->addWidget(rotation_x,1,2);
    grid->addWidget(rotation_label_y,1,3);
    grid->addWidget(rotation_y,1,4);
    grid->addWidget(rotation_label_z,1,5);
    grid->addWidget(rotation_z,1,6);

    //Rotation connections
    connect(rotation_x,SIGNAL(valueChanged(double)),this,SLOT(SetXRotation(double)));
    connect(rotation_y,SIGNAL(valueChanged(double)),this,SLOT(SetYRotation(double)));
    connect(rotation_z,SIGNAL(valueChanged(double)),this,SLOT(SetZRotation(double)));

    //Scale
    grid->addWidget(scale_label,2,0);
    grid->addWidget(scale_label_x,2,1);
    grid->addWidget(scale_x,2,2);
    grid->addWidget(scale_label_y,2,3);
    grid->addWidget(scale_y,2,4);
    grid->addWidget(scale_label_z,2,5);
    grid->addWidget(scale_z,2,6);

    //Scale connections
    connect(scale_x,SIGNAL(valueChanged(double)),this,SLOT(SetXScale(double)));
    connect(scale_y,SIGNAL(valueChanged(double)),this,SLOT(SetYScale(double)));
    connect(scale_z,SIGNAL(valueChanged(double)),this,SLOT(SetZScale(double)));

    main_layout->addLayout(grid);

    setLayout(main_layout);
}

void TransformWidget::GetEntityValues(QVector3D position, QVector3D rotation, QVector3D scale)
{
    position_x->setValue(position.x());
    position_y->setValue(position.y());
    position_z->setValue(position.z());

    rotation_x->setValue(rotation.x());
    rotation_y->setValue(rotation.y());
    rotation_z->setValue(rotation.z());

    scale_x->setValue(scale.x());
    scale_y->setValue(scale.y());
    scale_z->setValue(scale.z());
}

void TransformWidget::SetXPosition(double value)
{
    if(selcted_entity_transform)
        selcted_entity_transform->SetXPosition(value);
}

void TransformWidget::SetYPosition(double value)
{
    if(selcted_entity_transform)
        selcted_entity_transform->SetYPosition(value);
}

void TransformWidget::SetZPosition(double value)
{
    if(selcted_entity_transform)
        selcted_entity_transform->SetZPosition(value);
}

void TransformWidget::SetXRotation(double value)
{
    if(selcted_entity_transform)
        selcted_entity_transform->SetXRotation(value);
}

void TransformWidget::SetYRotation(double value)
{
    if(selcted_entity_transform)
        selcted_entity_transform->SetYRotation(value);
}

void TransformWidget::SetZRotation(double value)
{
    if(selcted_entity_transform)
        selcted_entity_transform->SetZRotation(value);
}

void TransformWidget::SetXScale(double value)
{
    if(selcted_entity_transform)
        selcted_entity_transform->SetXScale(value);
}

void TransformWidget::SetYScale(double value)
{
    if(selcted_entity_transform)
        selcted_entity_transform->SetYScale(value);
}

void TransformWidget::SetZScale(double value)
{
    if(selcted_entity_transform)
        selcted_entity_transform->SetZScale(value);
}


