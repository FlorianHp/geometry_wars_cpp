#include "SExplosion.h"
#include "EntityManager.h"

void SExplosion::spawn(Context& ctx, const Vec2& pos, float power) {

  auto e = ctx.entities.addEntity("explosion");

  e->cTransform = std::make_shared<CTransform>(
    pos,
    Vec2(0.f, 0.f),
    0.f
  );

  float size = 75.f * power;

  e->cShape = std::make_shared<CShape>(
    size,
    size,
    sf::Color::White
  );

  if (ctx.dummyTexture) {
    e->cShape->rect.setTexture(ctx.dummyTexture.get());
  }

  e->cExplosion = std::make_shared<CExplosion>(
    2.0f,
    power
  );
}

void SExplosion::update(Context& ctx, float dt) {

  for (auto& e : ctx.entities.getEntities("explosion")) {
    if (!e->cExplosion) continue;

    e->cExplosion->time += dt;

    if (e->cExplosion->time > e->cExplosion->lifetime) {
        e->destroy();
        ctx.entities.entityDied = true;
        continue;
    }

    float t = e->cExplosion->time / e->cExplosion->lifetime;
    float s = 1.0f + t * 2.0f;

    if (e->cShape && e->cShape->useRect) {
        auto& r = e->cShape->rect;
        sf::Vector2f base = r.getSize();
        r.setScale({s, s});
    }
  }
}