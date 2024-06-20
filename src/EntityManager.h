#pragma once

#include <vector>
#include <memory>
#include <map>
#include "Entity.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVector;
typedef std::map<std::string, EntityVector> EntityMap;

class EntityManager
{
private:
    EntityVector entities;
    EntityVector toAdd;
    EntityMap entityMap;
    size_t totalEntities = 0;

public:
    EntityManager();
    void update();
    std::shared_ptr<Entity> addEntity(const std::string &tag);
    EntityVector &getEntities();
    EntityVector &getEntities(const std::string &tag);
};
