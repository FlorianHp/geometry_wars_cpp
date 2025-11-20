#include "SUserInput.h"
#include "SBullet.h"


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

        SBullet::spawnBullet(ctx, Vec2(mouseButtonPressed->position.x, mouseButtonPressed->position.y));
      }
    }
  }
}



