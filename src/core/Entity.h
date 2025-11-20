#pragma once

#include "Components.h"
#include <memory>
#include <string>

class Entity {
    friend class EntityManager;

    bool        m_active  = true;
    size_t      m_id      = 0;
    std::string m_tag     = "default";

    Entity(const size_t id, const std::string& tag);

  public:

    std::shared_ptr<CTransform>  cTransform;
    std::shared_ptr<CShape>      cShape;
    std::shared_ptr<CInput>      cInput;
    std::shared_ptr<CScore>      cScore;
    std::shared_ptr<CLifespan>   cLifespan;
    std::shared_ptr<CProjectile> cProjectile;
    std::shared_ptr<COwner>      cOwner;
    std::shared_ptr<CDamage>     cDamage;
    std::shared_ptr<CExplosion>  cExplosion;

    bool isActive() const;
    const std::string& tag() const;
    const size_t id() const;
    void destroy();
    void reactivate();
};