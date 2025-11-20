#pragma once
#include "core/Context.h"

struct SBullet {
  static void update(Context &ctx);
  static void spawnBullet(Context& ctx, const Vec2 &target);
};