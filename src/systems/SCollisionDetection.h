#pragma once
#include "../core/Context.h"
#include <vector>

struct Contact {
  std::shared_ptr<Entity> A;
  std::shared_ptr<Entity> B;
  Vec2 normal;
  float penetration;
  float restitution;
};

struct SCollisionDetection {
  static std::vector<Contact> compute(Context& ctx);
};