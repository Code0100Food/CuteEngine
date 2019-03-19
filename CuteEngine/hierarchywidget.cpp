#include "hierarchywidget.h"
#include "mainwindow.h"
#include "mainscene.h"
#include "QVBoxLayout"
#include "entity.h"
#include "qt_application.h"
#include "inspector.h"

HierarchyWidget::HierarchyWidget(QWidget* parent) : QWidget(parent)
{
    Start();
}

HierarchyWidget::~HierarchyWidget()
{
    widget_entity_list->selectAll();
    qDeleteAll(widget_entity_list->selectedItems());
    delete widget_entity_list;

    delete add_entity;
    delete remove_entity;
}

void HierarchyWidget::Start()
{
   //Set Up the Hierarchy window
   //Entity list
   widget_entity_list = new QListWidget();
   widget_entity_list->setSelectionMode(QAbstractItemView::ExtendedSelection);

   connect(widget_entity_list, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(SelectedEntity()));

   //Add/Remove Entity
   add_entity = new QPushButton("Add Entity");
   remove_entity = new QPushButton("Remove Entity");

   connect(add_entity, SIGNAL(clicked(bool)), this, SLOT(AddEntity()));
   connect(remove_entity, SIGNAL(clicked(bool)), this, SLOT(RemoveEntity()));

  //Layout of Hierarchy
  QVBoxLayout* _layout = new QVBoxLayout();

  _layout->addWidget(widget_entity_list);
  _layout->addWidget(add_entity);
  _layout->addWidget(remove_entity);

  setLayout(_layout);
}

void HierarchyWidget::AddEntity()
{
    //Add Entity to the Logic List
    Entity* new_entity = new Entity(id);
    customApp->main_scene()->AddEntity(new_entity);

    //Add entity to the UI List
    widget_entity_list->addItem(new_entity->GetName().c_str());
    SetNewEntitySelected(new_entity->GetName());
    id++;
}

void HierarchyWidget::RemoveEntity()
{
    QList<QListWidgetItem*> selected_items = widget_entity_list->selectedItems();

    foreach (QListWidgetItem* item, selected_items)
    {
        std::string entity_name = item->text().toStdString();
        std::cout<<entity_name<<std::endl;
        customApp->main_scene()->RemoveEntity(entity_name);

        widget_entity_list->removeItemWidget(item);
        delete item;
    }
}

QList<QListWidgetItem*> HierarchyWidget::GetSelectedItems() const
{
    return widget_entity_list->selectedItems();
}

void HierarchyWidget::SelectedEntity()
{
    QList<QListWidgetItem*> selected_items = widget_entity_list->selectedItems();
    customApp->main_window()->inspector()->SetName(selected_items[0]->text());

    customApp->main_scene()->SetSelectedEntity(selected_items[0]->text().toStdString());
}

QListWidgetItem* HierarchyWidget::FindEntity(std::string entity_name)
{
    for(int i = 0; i < widget_entity_list->count(); i++)
    {
        if(widget_entity_list->item(i)->text().toStdString() == entity_name)
          return widget_entity_list->item(i);
    }

    return nullptr;
}

void HierarchyWidget::SetNewEntitySelected(std::string name)
{
    for(int i = 0; i < widget_entity_list->count(); i++)
    {
        widget_entity_list->setItemSelected(widget_entity_list->item(i), false);
    }
    widget_entity_list->setItemSelected(FindEntity(name), true);
}




















