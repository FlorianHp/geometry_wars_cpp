#pragma once

#include "core/Context.h"

struct SUserInput {
  static void spawnBullet(Context& ctx, const Vec2 &target);
  static void update(Context& ctx);
};