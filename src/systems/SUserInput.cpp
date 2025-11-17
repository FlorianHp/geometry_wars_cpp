#include "SUserInput.h"


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

  auto bullet = ctx.entities.addEntity("bullet");

  bullet->cTransform = std::make_shared<CTransform>(target, Vec2(0, 0), 0);
  bullet->cShape     = std::make_shared<CShape>(10.0f, 8, sf::Color(255, 255, 255), sf::Color(255, 0, 0), 2.0f);
}

