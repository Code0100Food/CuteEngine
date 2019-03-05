#include "inspector.h"
#include "ui_inspector.h"

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

    ui->AddComponentComboBox->setCurrentIndex(0);
}

void inspector::CreateBasicPrimitive()
{

    ui->AddComponentComboBox->setCurrentIndex(0);
}

void inspector::on_AddComponentComboBox_currentIndexChanged(const QString &string)
{
    if (string == "Transform")
        CreateTransformation();
    else if (string == "Basic Primitive")
        CreateBasicPrimitive();
}
