#include "SRender.h"

#include <iostream>


void SRender::update(Context& ctx) {

    ctx.window.clear();

    for (auto& e : ctx.entities.getEntities()) {

        sf::Shape* shape = nullptr;

        if (e->cShape->useRect) {
            shape = &e->cShape->rect;
        } else {
            shape = &e->cShape->circle;
        }

        shape->setPosition({e->cTransform->pos.x, e->cTransform->pos.y});
        e->cTransform->angle += 1.0f;
        shape->setRotation(sf::degrees(e->cTransform->angle));

        auto tag = e->tag();

        if ( tag == "explosion" && ctx.explosionShader ) {

          ctx.explosionShader->setUniform("t", e->cExplosion->time);
          ctx.explosionShader->setUniform("power", e->cExplosion->power);
          ctx.window.draw(e->cShape->rect, ctx.explosionShader.get());
          continue;
        } else if (tag == "bullet" && ctx.bulletShader) {

            ctx.bulletShader->setUniform("time", ctx.clock.getElapsedTime().asSeconds());
            ctx.window.draw(*shape, ctx.bulletShader.get());
            continue;
        } else {

            ctx.window.draw(*shape);
        }
    }

    ctx.window.draw(*ctx.scoreText);

    ctx.window.display();
}