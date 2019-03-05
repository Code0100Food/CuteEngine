#include "mainscene.h"
#include "qt_application.h"

MainScene::MainScene()
{

}

MainScene::~MainScene()
{
    RemoveEntities();
}

void MainScene::SetApp(qt_Application* _app)
{
    app = _app;
}

void MainScene::AddEntity(Entity *new_entity)
{
    if (new_entity != nullptr)
        entities.push_front(new_entity);

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
         if((*item)->name == entity_to_remove)
         {
             delete(*item);
             item = entities.erase(item);

             std::cout<< "Removed " << entity_to_remove << std::endl;
             break;
         }
     }
 }
