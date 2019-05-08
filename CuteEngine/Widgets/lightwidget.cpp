#include "lightwidget.h"
#include "QComboBox"
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>
#include <iostream>
#include <QColorDialog>
#include <QPushButton>
#include <QPalette>
#include "qt_application.h"
#include "mainscene.h"
#include "entity.h"
#include "light.h"

LightWidget::LightWidget()
{
    //UI initialization
    QVBoxLayout* main_layout = new QVBoxLayout();

    QGridLayout* grid = new QGridLayout();

    //Window title
    QLabel* title = new QLabel("Light Component");
    main_layout->addWidget(title);

    //Label
    select_light_type = new QLabel("Light type: ");
    grid->addWidget(select_light_type, 0, 0);

    //Selector
    light_type = new QComboBox();
    light_type->addItem("Directional");
    light_type->addItem("Point");
    grid->addWidget(light_type, 0, 1);

    connect(light_type, SIGNAL(currentIndexChanged(int)), this, SLOT(ChangedLightType(int)));

    //Intensity
    QLabel* select_light_intensity = new QLabel("Light intensity: ");
    grid->addWidget(select_light_intensity, 1, 0);

    light_intensity = new QSlider(Qt::Orientation::Horizontal);
    light_intensity->setRange(0, 1000);
    light_intensity->setValue(1);
    //light_intensity->setTracking(true);
    grid->addWidget(light_intensity, 1, 1);

    intensity = new QLabel("0");
    grid->addWidget(intensity, 1, 2);

    connect(light_intensity, SIGNAL(valueChanged(int)), this, SLOT(ChangedIntensity()));

    //Color
    QLabel* color_label = new QLabel("Color: ");
    grid->addWidget(color_label, 2, 0);

    color_picker = new QPushButton();
    color_picker->setStyleSheet("background-color: white");
    grid->addWidget(color_picker, 2, 1);

    connect(color_picker, SIGNAL(released()), this, SLOT(ChangedColor()));

    //LightRadius
    radius_label = new QLabel("Radius: ");
    grid->addWidget(radius_label, 3, 0);

    light_radius = new QSlider(Qt::Orientation::Horizontal);
    light_radius->setRange(0, 1000);
    light_radius->setValue(10);
    grid->addWidget(light_radius, 3, 1);

    radius_label_value = new QLabel("0");
    grid->addWidget(radius_label_value, 3, 2);

    radius_label->hide();
    light_radius->hide();
    radius_label_value->hide();

    connect(light_radius, SIGNAL(valueChanged(int)), this, SLOT(ChangedRadius()));

    main_layout->addLayout(grid);
    setLayout(main_layout);

}

void LightWidget::ChangedIntensity()
{
    intensity->setText(QString::number(light_intensity->value()));

    Light* light_component = (Light*)customApp->main_scene()->GetSelectedEntity()->FindComponent(COMPONENT_TYPE::COMPONENT_LIGHT);
    if(light_component)
    {
        light_component->SetIntensity(light_intensity->value());
    }
}

void LightWidget::ChangedRadius()
{
    radius_label_value->setText(QString::number(light_radius->value()));

    Light* light_component = (Light*)customApp->main_scene()->GetSelectedEntity()->FindComponent(COMPONENT_TYPE::COMPONENT_LIGHT);
    if(light_component)
    {
        light_component->SetRadius(light_radius->value());
    }
}

void LightWidget::ChangedColor()
{
    QColor col = QColorDialog::getColor(Qt::white);
    if(col.isValid())
    {
        QString qss = QString("background-color: %1").arg(col.name());
        color_picker->setStyleSheet(qss);

        //Update color
        int red, green, blue, alpha;
        col.getRgb(&red, &green, &blue, &alpha);
        QVector4D new_color((red/255.0f), (green/255.0f), (blue/255.0f), (alpha/255.0f));

        Light* light_component = (Light*)customApp->main_scene()->GetSelectedEntity()->FindComponent(COMPONENT_TYPE::COMPONENT_LIGHT);
        if(light_component)
        {
            light_component->SetColor(new_color);
        }
    }

}

void LightWidget::ChangedLightType(int value)
{
    if(value == 0) //Directional
    {
        radius_label->hide();
        light_radius->hide();
        radius_label_value->hide();

        //Update entity
        ChangeLightType(0);
    }

    if(value == 1) //point
    {
        radius_label->show();
        light_radius->show();
        radius_label_value->show();

         ChangeLightType(1);
    }


}

void LightWidget::ChangeLightType(int new_type)
{
    Light* light_component = (Light*)customApp->main_scene()->GetSelectedEntity()->FindComponent(COMPONENT_TYPE::COMPONENT_LIGHT);
    if(light_component)
    {
        light_component->SetType((LIGHTTYPE)new_type);
    }
}
