#include "transform.h"
#include <QPushButton>
#include <QVBoxLayout>
#include <iostream>
#include <QGridLayout>
#include <QDoubleSpinBox>
#include <QLabel>

Transform::Transform(QWidget *aParent) : Component(aParent)
{
    type = COMPONENT_TYPE::COMPONENT_TRANSFORM;

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
    QDoubleSpinBox* position_x = new QDoubleSpinBox();
    QDoubleSpinBox* position_y = new QDoubleSpinBox();
    QDoubleSpinBox* position_z = new QDoubleSpinBox();
    QDoubleSpinBox* rotation_x = new QDoubleSpinBox();
    QDoubleSpinBox* rotation_y = new QDoubleSpinBox();
    QDoubleSpinBox* rotation_z = new QDoubleSpinBox();
    QDoubleSpinBox* scale_x = new QDoubleSpinBox();
    QDoubleSpinBox* scale_y = new QDoubleSpinBox();
    QDoubleSpinBox* scale_z = new QDoubleSpinBox();

    //Position
    grid->addWidget(position_label,0,0);
    grid->addWidget(position_label_x,0,1);
    grid->addWidget(position_x,0,2);
    grid->addWidget(position_label_y,0,3);
    grid->addWidget(position_y,0,4);
    grid->addWidget(position_label_z,0,5);
    grid->addWidget(position_z,0,6);
    //Rotation
    grid->addWidget(rotation_label,1,0);
    grid->addWidget(rotation_label_x,1,1);
    grid->addWidget(rotation_x,1,2);
    grid->addWidget(rotation_label_y,1,3);
    grid->addWidget(rotation_y,1,4);
    grid->addWidget(rotation_label_z,1,5);
    grid->addWidget(rotation_z,1,6);
    //Scale
    grid->addWidget(scale_label,2,0);
    grid->addWidget(scale_label_x,2,1);
    grid->addWidget(scale_x,2,2);
    grid->addWidget(scale_label_y,2,3);
    grid->addWidget(scale_y,2,4);
    grid->addWidget(scale_label_z,2,5);
    grid->addWidget(scale_z,2,6);

    main_layout->addLayout(grid);

    setLayout(main_layout);
}

Transform::~Transform()
{

}
