#pragma once

#include "core/Context.h"

struct SEnemySpawner {
  static void spawnEnemy(Context& ctx);
  static void spawnSmallEnemies(std::shared_ptr<Entity> e);
  static void update(Context& ctx);
};