#include "mainscene.h"
#include "qt_application.h"
#include "entity.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "hierarchywidget.h"
#include "inspector.h"
#include "component.h"
#include <QVBoxLayout>

MainScene::MainScene()
{
    BackgroundColor = QVector4D(0.0f, 0.5f, 0.0f, 1.0f);
}

MainScene::~MainScene()
{
    for(std::list<Entity*>::iterator item = entities.begin(); item != entities.end(); item++)
    {
        if(*item != nullptr)
        {
            delete (*item);
        }
    }
    entities.clear();
}

void MainScene::Update()
{
    for(std::list<Entity*>::iterator item = entities.begin(); item != entities.end(); item++)
    {
        item._Ptr->_Myval->Update();
    }
}

void MainScene::Draw()
{
    for(std::list<Entity*>::iterator item = entities.begin(); item != entities.end(); item++)
    {
        (*item)->Draw();
    }
}

void MainScene::AddEntity(Entity *new_entity)
{
    if (new_entity != nullptr)
    {
        entities.push_back(new_entity);
        SetSelectedEntity(new_entity->GetName());
    }

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
      selected_entity = nullptr;
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

 Entity* MainScene::GetSelectedEntity()const
 {
     return selected_entity;
 }

 void MainScene::SetSelectedEntity(std::string entity_name)
 {   
    Entity* cur_select = FindEntity(entity_name);

    if(cur_select != nullptr)
    {
        if(selected_entity != nullptr)
        {
            selected_entity->Deselect();
        }

        selected_entity = cur_select;
        if(selected_entity != nullptr)
        {
            selected_entity->Select();
            customApp->main_window()->inspector()->UIReadEntity(selected_entity);

        }
    }
    else
    {
        customApp->main_window()->inspector()->HideUI();

    }

 }

 Entity* MainScene::FindEntity(std::string entity_name)
 {
     for(std::list<Entity*>::iterator item = entities.begin(); item != entities.end(); item++)
     {
         if((*item)->GetName() == entity_name)
             return(*item);
     }

     return nullptr;
 }

 void MainScene::RenameSelectedEntity(std::string new_entity_name)
 {
     if(selected_entity)
     {
         customApp->main_window()->hierarchy()->FindEntity(selected_entity->GetName())->setText(new_entity_name.c_str());
         selected_entity->SetName(new_entity_name);
     }
 }

 void MainScene::SetBackgroundColor(const QVector4D new_color)
 {
    BackgroundColor = new_color;
 }

 const QVector4D MainScene::GetBackgroundColor()const
 {
    return BackgroundColor;
 }

 bool MainScene::IsGridPrint()const
 {
     return print_grid;
 }

 void MainScene::SetGridPrint(bool _print_grid)
 {
     print_grid = _print_grid;
 }
