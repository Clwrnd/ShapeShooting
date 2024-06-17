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
}

EntityVector& EntityManager::getEntities(){
    return entities;
}