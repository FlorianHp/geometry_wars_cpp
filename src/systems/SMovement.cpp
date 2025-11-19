#include "SMovement.h"

#include <iostream>


void SMovement::update(Context& ctx, float dt) {
  (void)dt;
  
  if (ctx.entities.getEntities("player").empty() || !ctx.entities.getEntities("player")[0]) {
    std::cerr << "⚠️ No Player found \n";
  } else {

    auto& player = ctx.entities.getEntities("player")[0];

    if (!player || !player->cInput || !player->cTransform) {
      std::cerr << "⚠️ Player invalid or missing components\n";
      return;
    }

    player->cTransform->velocity = { 0, 0 };

    if (player->cInput->up   ) player->cTransform->velocity.y = -5;
    if (player->cInput->down ) player->cTransform->velocity.y =  5;
    if (player->cInput->left ) player->cTransform->velocity.x = -5;
    if (player->cInput->right) player->cTransform->velocity.x =  5;
  }

  for (auto &e : ctx.entities.getEntities()) {

    if (!e->cTransform) {
      
      std::cerr << "❌ Entity with tag '" << e->tag() << "' has no CTransform!\n";
      continue;
    } 

    e->cTransform->pos.x += e->cTransform->velocity.x;
    e->cTransform->pos.y += e->cTransform->velocity.y;
  }
}