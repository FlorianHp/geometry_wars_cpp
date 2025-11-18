#include "SBullet.h"

#include <algorithm>
#include <cmath>

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