#include "systems/SCollisionResponse.h"

#include <algorithm>
#include <cmath>
#include <set>

void SCollisionResponse::resolve(Context& ctx, std::vector<Contact>& contacts) {

  static std::set<std::pair<size_t, size_t>> handledPairs;
  handledPairs.clear();

  for (auto& c : contacts) {
    auto& e = c.A;
    auto& a = c.B;

    auto idA = e->id(); 
    auto idB = a->id();
    auto key = std::minmax(idA, idB);

    if (handledPairs.count(key)) continue;
    handledPairs.insert(key);

    if (e->tag() == "bullet" && a->tag() == "bullet") continue;

    if (e->tag() == "enemy" && a->tag() == "enemy") {
      for (auto& s : ctx.bounceSounds) {
        if (s.getStatus() == sf::SoundSource::Status::Stopped) {
          s.setVolume(50.f);
          s.play();
          break;
        }
      }

      Vec2 rv = a->cTransform->velocity - e->cTransform->velocity;
      float velAlongNormal = rv.dot(c.normal);
      if (velAlongNormal > 0.0f) continue;

      float restitution = 0.8f;

      float invMassA = 1.0f;
      float invMassB = 1.0f;

      float j = -(1 + restitution) * velAlongNormal / (invMassA + invMassB);

      Vec2 impulse = c.normal * j;
      e->cTransform->velocity -= impulse * invMassA;
      a->cTransform->velocity += impulse * invMassB;

      const float percent = 0.8f;
      const float slop    = 0.01f;

      float correctionMag = std::max(c.penetration - slop, 0.0f) / (invMassA + invMassB) * percent;
      Vec2 correction = c.normal * correctionMag;

      e->cTransform->pos -= correction * invMassA;
      a->cTransform->pos += correction * invMassB;

      for (auto& s : ctx.bounceSounds) {
        if (s.getStatus() == sf::SoundSource::Status::Stopped) {
          s.setVolume(60.f);
          s.play();
          break;
        }
      } 
    } else {
      e->destroy();
      a->destroy();

      ctx.entities.entityDied = true;

      for (auto& s : ctx.explosionSounds) {
        if (s.getStatus() == sf::SoundSource::Status::Stopped) {
          s.setVolume(60.f);
          s.play();
          break;
        }
      } 
    }
  }
}

void SCollisionResponse::resolveWallCollisions(Context& ctx) {
  auto windowSize = ctx.window.getSize();

  for (auto& e : ctx.entities.getEntities("enemy")) {
    if (!e->cTransform || !e->cShape) continue;

    float radius = e->cShape->circle.getRadius();
    Vec2& pos    = e->cTransform->pos;
    Vec2& vel    = e->cTransform->velocity;

    bool bounced = false;

    if (pos.x + radius >= windowSize.x) {
      pos.x   = windowSize.x - radius;
      vel.x  *= -1;
      bounced = true;
    } else if (pos.x - radius <= 0) {
      pos.x   = radius;
      vel.x  *= -1;
      bounced = true;
    }

    if (pos.y + radius >= windowSize.y) {
      pos.y   = windowSize.y - radius;
      vel.y  *= -1;
      bounced = true;
    } else if (pos.y - radius <= 0) {
      pos.y   = radius;
      vel.y  *= -1;
      bounced = true;
    }
  }
}