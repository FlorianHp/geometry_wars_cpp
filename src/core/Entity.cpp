#include "Entity.h"


Entity::Entity(const size_t id, const std::string &tag)
  : m_id(id),
    m_tag(tag),
    m_active(true) {}

bool Entity::isActive() const {
  return this->m_active;
}

const std::string& Entity::tag() const {
  return this->m_tag;
}

const size_t Entity::id() const{
  return this->m_id;
}

void Entity::destroy() {
  this->m_active = false;
}

void Entity::reactivate() {
  m_active = true;
}
  
