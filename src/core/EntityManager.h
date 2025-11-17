#pragma once
#include "Entity.h"

#include <memory>
#include <vector>
#include <unordered_map>
#include <string>
#include <random>

using EntityVec = std::vector<std::shared_ptr<Entity>>;

class EntityManager {
public:
    EntityManager();

    void update();
    std::shared_ptr<Entity> addEntity(const std::string &tag);
    const EntityVec &getEntities();
    const EntityVec &getEntities(const std::string &tag);
    float randFloat(float min, float max);
    int   randInt(int min, int max);

    bool entityDied = false;

private:
    void removeDeadEntities(EntityVec &vec);
    
    std::random_device m_random;
    std::mt19937       m_rng;
    EntityVec          m_entities;
    EntityVec          m_entitiesToAdd;
    std::unordered_map<std::string, EntityVec> m_entityMap;
    size_t             m_totalEntities = 0;
};
