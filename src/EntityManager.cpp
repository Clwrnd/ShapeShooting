#include "EntityManager.h"

EntityManager::EntityManager(){};

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag)
{
    auto e = std::shared_ptr<Entity>(new Entity(totalEntities++, tag));
    toAdd.push_back(e);
    return e;
}

void EntityManager::update()
{
    for (auto e : toAdd)
    {
        entities.push_back(e);
        entityMap[e->getTag()].push_back(e);
    }
    toAdd.clear();

    auto it = std::remove_if(entities.begin(),entities.end(),[](std::shared_ptr<Entity> e){return ! e->isActive();} );
    entities.erase(it,entities.end());
    for (auto & [tag,entityV]:entityMap)
    {
        auto it = std::remove_if(entityV.begin(),entityV.end(),[](std::shared_ptr<Entity> e){return ! e->isActive();} );    
        entityV.erase(it,entityV.end());
    }
}

EntityVector& EntityManager::getEntities(){
    return entities;
}

EntityVector& EntityManager::getEntities(const std::string & tag)
{
    return entityMap[tag];
} 