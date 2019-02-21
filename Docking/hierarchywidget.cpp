#include "hierarchywidget.h"
#include "QVBoxLayout"

int id = 0;

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
    std::string test = "Entity_";
    char buffer[10];
    itoa(id, buffer, 10);
    std::string tes_1t = buffer;

    test += tes_1t;

    widget_entity_list->addItem(test.c_str());
    id++;
}

void HierarchyWidget::RemoveEntity()
{
    QList<QListWidgetItem*> selected_items = widget_entity_list->selectedItems();

    foreach (QListWidgetItem* item, selected_items) {
        widget_entity_list->removeItemWidget(item);
        delete item;
    }
}
