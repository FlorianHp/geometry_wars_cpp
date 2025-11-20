#pragma once
#include "Context.h"

struct SExplosion {

public:

  static void update(Context& ctx, float dt);

  static void spawn(Context& ctx, const Vec2& pos, float power = 1.0f);
};