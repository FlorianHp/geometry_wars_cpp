#include "SRender.h"


void SRender::update(Context& ctx) {

  ctx.window.clear();

  for (auto& e : ctx.entities.getEntities()) {

    e->cShape->circle.setPosition(sf::Vector2f(e->cTransform->pos.x, e->cTransform->pos.y));
    e->cTransform->angle += 1.0f;
    e->cShape->circle.setRotation(sf::degrees(e->cTransform->angle));

    ctx.window.draw(e->cShape->circle);
  }

  ctx.window.display();
}