#include "lightwidget.h"
#include "QComboBox"
#include <QLabel>
#include <QVBoxLayout>
#include <QGridLayout>

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

    main_layout->addLayout(grid);
    setLayout(main_layout);

}
