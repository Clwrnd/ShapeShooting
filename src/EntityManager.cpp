#include"EntityManager.h"

std::shared_ptr<Entity> EntityManager::addEntity (const std::string & tag){
    auto e = std::make_shared<Entity>(tag,totalEntities++);
    toAdd.push_back(e);
    return e; 
}

void EntityManager::update(){
    for (auto e: toAdd){
        entities.push_back(e);
        entityMap[e -> tag()].push_back(e);
    }
    toAdd.clear(); 
}