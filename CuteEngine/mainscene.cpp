#include "mainscene.h"
#include "qt_application.h"
#include "entity.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hierarchywidget.h"

MainScene::MainScene()
{

}

MainScene::~MainScene()
{
    for(std::list<Entity*>::iterator item = entities.begin(); item != entities.end(); item++)
    {
        delete (*item);
    }
    entities.clear();
}

void MainScene::AddEntity(Entity *new_entity)
{
    if (new_entity != nullptr)
        entities.push_back(new_entity);

    std::cout<<entities.size()<<std::endl;
}

 void MainScene::RemoveEntities()
 {
     for(std::list<Entity*>::iterator item = entities.begin(); item != entities.end(); item++)
     {
         delete (*item);
     }
     entities.clear();
 }

 void MainScene::RemoveEntity(std::string entity_to_remove)
  {
      for(std::list<Entity*>::iterator item = entities.begin(); item != entities.end(); item++)
      {
          if((*item)->GetName() == entity_to_remove)
          {
              delete(*item);
              item = entities.erase(item);

              std::cout<< "Removed " << entity_to_remove << std::endl;
              break;
          }
      }
  }

 std::list<Entity*> MainScene::GetSelectedEntities()const
 {
    std::list<Entity*> selected_entities;

     QList<QListWidgetItem*> selected_items = customApp->main_window()->hierarchy()->GetSelectedItems();

    foreach (QListWidgetItem* item, selected_items)
    {
        for(std::list<Entity*>::const_iterator entity_item = entities.begin(); entity_item != entities.end(); entity_item++)
        {
            if((*entity_item)->GetName() == item->text().toStdString())
            {
                selected_entities.push_back(*entity_item);
            }
        }
    }
    return selected_entities;
 }
