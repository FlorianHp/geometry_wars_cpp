#include "SCollisionDetection.h"
#include <cmath>

std::vector<Contact> SCollisionDetection::compute(Context& ctx) {

  std::vector<Contact> contacts;
  
  auto& entities = ctx.entities.getEntities();

  for (size_t i = 0; i < entities.size(); ++i) {
    auto& e = entities[i];

    if (e->tag() == "explosion" || !e->cTransform || !e->cShape ) continue;

    for (size_t j = i + 1; j < entities.size(); ++j) {
      auto& a = entities[j];

      if ( a->tag() == "explosion" || !a->cTransform || !a->cShape ) continue;

      Vec2 delta = a->cTransform->pos - e->cTransform->pos;
      float distSq = delta.x * delta.x + delta.y * delta.y;

      float combinedRadius = e->cShape->circle.getRadius() + a->cShape->circle.getRadius();

      if (distSq <= combinedRadius * combinedRadius && distSq > 0.0f) {
        float dist = std::sqrt(distSq);
        Vec2 normal = delta / dist;
        float penetration = combinedRadius - dist;

        contacts.push_back({ e, a, normal, penetration, 1.0f });
      }
    }
  }

  return contacts;
}