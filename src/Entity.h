#pragma once

#include <string>
#include "Component.h"
#include <memory>

class Entity
{
    friend class EntityManager;

private:
    bool active = true;
    size_t id = 0;
    std::string tag = "default";

    Entity(const size_t id_in, const std::string &tag_in);

public:
    std::shared_ptr<CTransform> cTransform;
    std::shared_ptr<CShape> cShape;
    std::shared_ptr<CCollision> cCollision;
    std::shared_ptr<CScore> cScore;
    std::shared_ptr<CLifespan> cLifespan;
    std::shared_ptr<CInput> cInput;
    std::shared_ptr<CDelayedeffect> cDelayedeffect;
    std::shared_ptr<CWave> cWave;

    bool isActive() const;
    const size_t getId() const;
    const std::string &getTag() const;
    void destroy();
};
