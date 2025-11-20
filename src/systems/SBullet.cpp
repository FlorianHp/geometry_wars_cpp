#include "SBullet.h"

#include <algorithm>
#include <cmath>

namespace {
  constexpr float BULLET_SPEED     = 15.0f;
  constexpr float BULLET_RANGE     = 400.0f;
  constexpr float BULLET_FADE_FROM = 0.8f;
  constexpr int   BULLET_DAMAGE    = 1;
}

void SBullet::update(Context &ctx) {

  for (auto &e : ctx.entities.getEntities("bullet")) {

    if (!e->cTransform || !e->cShape || !e->cProjectile) {
      continue;
    }

    auto &t = e->cTransform;
    auto &p = e->cProjectile;

    Vec2 diff    = t->pos - p->lastPos;
    float distSq = diff.x * diff.x + diff.y * diff.y;
    float dist   = (distSq > 0.0f) ? std::sqrt(distSq) : 0.0f;

    p->traveled += dist;
    p->lastPos   = t->pos;

    float fadeStartDist = p->maxDistance * p->fadeStartFactor;

    if (p->traveled >= fadeStartDist) {

      float fadeRange = p->maxDistance - fadeStartDist;
      float over      = p->traveled - fadeStartDist;

      float factor = 0.0f;
      if (fadeRange > 0.0f) {

        factor = 1.0f - std::clamp(over / fadeRange, 0.0f, 1.0f);
      }

      auto fill = e->cShape->circle.getFillColor();
      fill.a    = 255.0f * factor;
      e->cShape->circle.setFillColor(fill);

      auto outline = e->cShape->circle.getOutlineColor();
      outline.a    = fill.a;
      e->cShape->circle.setOutlineColor(outline);
    }

    if (p->traveled >= p->maxDistance) {
      e->destroy();

      ctx.entities.entityDied = true;
    }
  }
}

void SBullet::spawnBullet(Context& ctx, const Vec2 &target) {

  if (!ctx.player || !ctx.player->cTransform) {
    return;
  }

  auto bullet = ctx.entities.addEntity("bullet");

  Vec2 startPos = ctx.player->cTransform->pos;
  Vec2 dir      = target - startPos;
  float lenSq   = dir.x * dir.x + dir.y * dir.y;

  if (lenSq > 0.0f) {
    float len = std::sqrt(lenSq);
    dir       = dir / len;
  } else {
    dir       = Vec2(1.0f, 0.0f);
  }

  Vec2 velocity = dir * BULLET_SPEED;

  float angleRad = std::atan2(dir.y, dir.x);
  float angleDeg = angleRad * 180.0f / 3.14159265f;

  bullet->cTransform = std::make_shared<CTransform>(
    startPos,
    velocity,
    angleDeg
  );

  bullet->cShape = std::make_shared<CShape>(
    80.f,
    80.f,
    sf::Color::White
  );

  bullet->cShape->rect.setTexture(ctx.dummyTexture.get());

  bullet->cProjectile = std::make_shared<CProjectile>(
    startPos,
    BULLET_RANGE,
    BULLET_FADE_FROM
  );

  bullet->cOwner = std::make_shared<COwner>(ctx.player->id());

  bullet->cDamage = std::make_shared<CDamage>(BULLET_DAMAGE);
}