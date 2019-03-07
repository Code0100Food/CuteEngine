#include "inspector.h"
#include "ui_inspector.h"
#include "qt_application.h"
#include "mainscene.h"
#include "entity.h"

inspector::inspector(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::inspector)
{
    ui->setupUi(this);
}

inspector::~inspector()
{
    delete ui;
}

void inspector::CreateTransformation()
{
    std::list<Entity*> selected = customApp->main_scene()->GetSelectedEntities();
    for(std::list<Entity*>::const_iterator entity_item = selected.begin(); entity_item != selected.end(); entity_item++)
    {
        std::cout<<(*entity_item)->GetName()<<std::endl;
    }

    ui->AddComponentComboBox->setCurrentIndex(0);
}

void inspector::CreateBasicPrimitive()
{

    ui->AddComponentComboBox->setCurrentIndex(0);
}

void inspector::on_AddComponentComboBox_currentIndexChanged(const QString &string)
{
    if (string == "Transform")
    {
        CreateTransformation();
    }
    else if (string == "Basic Primitive")
    {
        CreateBasicPrimitive();
    }
}
