#pragma once

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include "Entity.h"

using EntityVec = std::vector<std::shared_ptr<Entity>>;

class EntityManager {
public:
    EntityManager();

    void update();
    std::shared_ptr<Entity> addEntity(const std::string &tag);
    const EntityVec &getEntities();
    const EntityVec &getEntities(const std::string &tag);
    void setDied(bool e);

private:
    void removeDeadEntities(EntityVec &vec);
    bool m_died = false;

    EntityVec m_entities;
    EntityVec m_entitiesToAdd;
    std::unordered_map<std::string, EntityVec> m_entityMap;
    size_t m_totalEntities = 0;
};
