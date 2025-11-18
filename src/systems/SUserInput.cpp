#include "SUserInput.h"

namespace {
  constexpr float BULLET_SPEED     = 10.0f;
  constexpr float BULLET_RANGE     = 300.0f;
  constexpr float BULLET_FADE_FROM = 0.8f;
  constexpr int   BULLET_DAMAGE    = 1;
}

void SUserInput::update(Context& ctx) {

  while (const std::optional event = ctx.window.pollEvent()) {

    if (event->is<sf::Event::Closed>()) {
      
      ctx.running = false;
    }

    if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      
      switch (keyPressed->scancode) {
        case sf::Keyboard::Scancode::W:
          ctx.player->cInput->up = true;
          break;
        case sf::Keyboard::Scancode::A:
          ctx.player->cInput->left = true;
          break;
        case sf::Keyboard::Scancode::S:
          ctx.player->cInput->down = true;
          break;
        case sf::Keyboard::Scancode::D:
          ctx.player->cInput->right = true;
          break;
        default: break;
      }
    }

    if (const auto *keyReleased = event->getIf<sf::Event::KeyReleased>()) {

      switch (keyReleased->scancode) {
        case sf::Keyboard::Scancode::W:
          ctx.player->cInput->up = false;
          break;
        case sf::Keyboard::Scancode::A:
          ctx.player->cInput->left = false;
          break;
        case sf::Keyboard::Scancode::S:
          ctx.player->cInput->down = false;
          break;
        case sf::Keyboard::Scancode::D:
          ctx.player->cInput->right = false;
          break;
        default: break;
      }
    }

    if (const auto *mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {

      if (mouseButtonPressed->button == sf::Mouse::Button::Left) {

        SUserInput::spawnBullet(ctx, Vec2(mouseButtonPressed->position.x, mouseButtonPressed->position.y));
      }
    }
  }
}

void SUserInput::spawnBullet(Context& ctx, const Vec2 &target) {

  if (!ctx.player || !ctx.player->cTransform) {
    return;
  }

  auto bullet = ctx.entities.addEntity("bullet");

  Vec2 startPos = ctx.player->cTransform->pos;
  Vec2 dir      = target - startPos;
  float lenSq   = dir.x * dir.x + dir.y * dir.y;

  if (lenSq > 0.0f) {
    float len = std::sqrt(lenSq);
    dir       = dir / len;
  } else {
    dir       = Vec2(1.0f, 0.0f);
  }

  Vec2 velocity = dir * BULLET_SPEED;

  float angleRad = std::atan2(dir.y, dir.x);
  float angleDeg = angleRad * 180.0f / 3.14159265f;

  bullet->cTransform = std::make_shared<CTransform>(
    startPos,
    velocity,
    angleDeg
  );

  const float radius = 6.0f;

  bullet->cShape = std::make_shared<CShape>(
    radius,
    12,
    sf::Color(255, 255, 255, 255),
    sf::Color(255, 0, 0, 255),
    1.0f);

  bullet->cProjectile = std::make_shared<CProjectile>(
    startPos,
    BULLET_RANGE,
    BULLET_FADE_FROM
  );

  bullet->cOwner = std::make_shared<COwner>(ctx.player->id());

  bullet->cDamage = std::make_shared<CDamage>(BULLET_DAMAGE);
}

