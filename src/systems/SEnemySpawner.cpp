
#include "SEnemySpawner.h"


void SEnemySpawner::update(Context& ctx) {

  if (ctx.currentFrame - ctx.lastEnemySpawnTime >= 200) {

    SEnemySpawner::spawnEnemy(ctx);
  }
}

void SEnemySpawner::spawnEnemy(Context& ctx) {

  auto entity = ctx.entities.addEntity("enemy");

  float ex = ctx.entities.randFloat(0 + ctx.enemyConfig.CR, ctx.window.getSize().x - ctx.enemyConfig.CR);
  float ey = ctx.entities.randFloat(0 + ctx.enemyConfig.CR, ctx.window.getSize().y - ctx.enemyConfig.CR);

  /**
   * @todo bug: enemies spawn on each other and get stuck
   */

  entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(ctx.entities.randFloat(-3, 3), ctx.entities.randFloat(-3, 3)), 1.0f);

  int r = ctx.entities.randInt(0, 255), 
      g = ctx.entities.randInt(0, 255), 
      b = ctx.entities.randInt(0, 255);

  entity->cShape = std::make_shared<CShape>(
    ctx.enemyConfig.SR, 
    ctx.entities.randInt(ctx.enemyConfig.VMIN, ctx.enemyConfig.VMAX), 
    sf::Color(r, g, b), 
    sf::Color(ctx.enemyConfig.OR, ctx.enemyConfig.OG, ctx.enemyConfig.OB), 
    ctx.enemyConfig.OT
  );

  for (auto& other : ctx.entities.getEntities("enemy")) {
    if (other == entity || !other->cTransform || !other->cShape) continue;

    float dx = entity->cTransform->pos.x - other->cTransform->pos.x;
    float dy = entity->cTransform->pos.y - other->cTransform->pos.y;
    float distSq = dx*dx + dy*dy;
    float minDist = entity->cShape->circle.getRadius() + other->cShape->circle.getRadius();

    if (distSq < minDist * minDist) {
      Vec2 dir = Vec2(dx, dy).normalized();
      entity->cTransform->pos += dir * (minDist * 1.1f);
    }
  }

  ctx.lastEnemySpawnTime = ctx.currentFrame;
}

void SEnemySpawner::spawnSmallEnemies(Context& ctx, std::shared_ptr<Entity> e) {

  std::vector<std::shared_ptr<Entity>> smallEnemies;

  static const Vec2 dirs[4] = {
    Vec2( 1,  0),
    Vec2(-1,  0),
    Vec2( 0,  1),
    Vec2( 0, -1)
};

  float radius      = e->cShape->circle.getRadius() / 2;
  float spawnOffset = radius * 1.1f;
  int points        = e->cShape->circle.getPointCount();
  auto  fill        = e->cShape->circle.getFillColor();
  auto  outline     = e->cShape->circle.getOutlineColor();
  float thick       = e->cShape->circle.getOutlineThickness();
  Vec2 pos          = e->cTransform->pos;
 
  for (int i = 0; i < 4; i++) {
    auto small = ctx.entities.addEntity("enemy");

    Vec2 smallPos = pos + dirs[i] * spawnOffset; 
    Vec2 vel = dirs[i] * 4.0f;

    small->cTransform = std::make_shared<CTransform>(smallPos, vel, 0.f);

    small->cShape = std::make_shared<CShape>(
      radius,
      points,
      fill, 
      outline,
      thick
    );
  }
}







