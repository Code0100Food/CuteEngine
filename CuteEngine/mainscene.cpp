#include "mainscene.h"
#include "qt_application.h"
#include "entity.h"

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

void MainScene::SetApp(qt_Application* _app)
{
    app = _app;
}

void MainScene::AddEntity(Entity *new_entity)
{
    if (new_entity != nullptr)
        entities.push_front(new_entity);


}

 void MainScene::RemoveEntities(std::list<std::string> entities_to_remove)
 {

 }
