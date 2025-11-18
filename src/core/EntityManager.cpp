#include "EntityManager.h"

EntityManager::EntityManager()
  : m_rng(m_random()) {

}

void EntityManager::update() {

  for (auto& e : m_entitiesToAdd) {

    m_entities.push_back(e);
    m_entityMap[e->tag()].push_back(e);
  }

  m_entitiesToAdd.clear();

  if (entityDied) {

    for (auto& [tag, entityVec] : m_entityMap) {
  
      removeDeadEntities(entityVec);
    }
  }

}

void EntityManager::removeDeadEntities(EntityVec &vec) {
  
  for (auto it = vec.begin(); it != vec.end(); ) {

    auto &e = *it;

    if (!e->m_active) {

      m_entities.erase(
          std::remove(m_entities.begin(), m_entities.end(), e),
          m_entities.end()
      );
      it = vec.erase(it);
    } else {
      
      ++it;
    }
  }
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string &tag) {

  auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));

  m_entitiesToAdd.push_back(entity);

  return entity;
}

const EntityVec &EntityManager::getEntities() {

  return m_entities;
}

const EntityVec &EntityManager::getEntities(const std::string &tag) {

  return m_entityMap[tag];
}

float EntityManager::randFloat(float min, float max) {

  std::uniform_real_distribution<float> dist(min, max);

  return dist(m_rng);
}

int EntityManager::randInt(int min, int max) {

  std::uniform_int_distribution<int> dist(min, max);

  return dist(m_rng);
}