#include "Game.h"

#include <iostream>
#include <fstream>
#include <random>
#include <SFML/Graphics.hpp>


Game::Game(const std::string &config)
: m_text(m_font, "", 24),
  m_rng(m_random()) {
  init(config);
}

void Game::init(const std::string &path) {
  

  if (!m_font.openFromFile("Asimovian-Regular.ttf")) {
    std::cerr << "Error loading font" << std::endl;
  }

  std::ifstream fin(path);
  if (!fin.is_open()) {
    std::cerr << "Error opening config file: " << path << std::endl;
    return;
  }

  std::string type;

  while (fin >> type) {

    if (type == "Window") {
      u_int width, height, frameLimit, fullscreen;
      fin >> width >> height >> frameLimit >> fullscreen;

      m_window.create(sf::VideoMode({width, height}),
        "Geometry War",
        sf::Style::Default,
        sf::State::Windowed
      );
      
      m_window.setFramerateLimit(frameLimit);
    }

    else if (type == "Player") {
      fin >> m_playerConfig.SR
          >> m_playerConfig.CR
          >> m_playerConfig.S
          >> m_playerConfig.FR >> m_playerConfig.FG >> m_playerConfig.FB
          >> m_playerConfig.OR >> m_playerConfig.OG >> m_playerConfig.OB
          >> m_playerConfig.OT 
          >> m_playerConfig.V;
    }

    else if (type == "Enemy") {
      fin >> m_enemyConfig.SR 
          >> m_enemyConfig.CR
          >> m_enemyConfig.SMIN >> m_enemyConfig.SMAX
          >> m_enemyConfig.OR >> m_enemyConfig.OG >> m_enemyConfig.OB
          >> m_enemyConfig.OT
          >> m_enemyConfig.VMIN >> m_enemyConfig.VMAX
          >> m_enemyConfig.L 
          >> m_enemyConfig.SI;
    }

    else if (type == "Bullet") {
      fin >> m_bulletConfig.SR 
          >> m_bulletConfig.CR
          >> m_bulletConfig.S
          >> m_bulletConfig.FR >> m_bulletConfig.FG >> m_bulletConfig.FB
          >> m_bulletConfig.OR >> m_bulletConfig.OG >> m_bulletConfig.OB
          >> m_bulletConfig.OT 
          >> m_bulletConfig.V
          >> m_bulletConfig.L;
    }
  }

  fin.close();
  spawnPlayer();
}

void Game::run() {

  while(m_running) {

    m_entities.update();
    m_entities.setDied(false);

    if (!m_paused) {

      sEnemySpawner();
      sMovement();
      sCollision();
      sUserInput();

      if ( !m_player || !m_player->isActive() ) {
        spawnPlayer();
      }
    }

    sRender();

    m_currentFrame++;
  }

}

void Game::setPaused(bool paused) {

}

void Game::spawnPlayer() {
  auto entity = m_entities.addEntity("player");
  
  entity->cTransform = std::make_shared<CTransform>(Vec2(m_window.getSize().x / 2, m_window.getSize().y / 2), Vec2(1.0f, 1.0f), 0.0f);

  entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(0, 0, 255), 4.0f);

  entity->cInput = std::make_shared<CInput>();

  m_player = entity;
}

void Game::spawnEnemy() {

  auto entity = m_entities.addEntity("enemy");

  float ex = randFloat(0 + m_enemyConfig.CR, m_window.getSize().x - m_enemyConfig.CR);
  float ey = randFloat(0 + m_enemyConfig.CR, m_window.getSize().y - m_enemyConfig.CR);
  
  entity->cTransform = std::make_shared<CTransform>(Vec2(ex, ey), Vec2(randFloat(-3, 3), randFloat(-3, 3)), 1.0f);

  int r = randInt(0, 255), 
      g = randInt(0, 255), 
      b = randInt(0, 255);

  entity->cShape = std::make_shared<CShape>(
    m_enemyConfig.SR, 
    randInt(m_enemyConfig.VMIN, m_enemyConfig.VMAX), 
    sf::Color(r, g, b), 
    sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB), 
    m_enemyConfig.OT
  );

  m_lastEnemySpawnTime = m_currentFrame;
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e) {
  /**
   * @todo shatter enemies
   */
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 &target) {

  auto bullet = m_entities.addEntity("bullet");

  bullet->cTransform = std::make_shared<CTransform>(target, Vec2(0, 0), 0);
  bullet->cShape     = std::make_shared<CShape>(10.0f, 8, sf::Color(255, 255, 255), sf::Color(255, 0, 0), 2.0f);
}

void Game::sRender() {

  m_window.clear();

  for (auto& e : m_entities.getEntities()) {

    e->cShape->circle.setPosition(sf::Vector2f(e->cTransform->pos.x, e->cTransform->pos.y));
    e->cTransform->angle += 1.0f;
    e->cShape->circle.setRotation(sf::degrees(e->cTransform->angle));

    m_window.draw(e->cShape->circle);
  }

  m_window.display();
}

void Game::sUserInput() {

  while (const std::optional event = m_window.pollEvent()) {

    if (event->is<sf::Event::Closed>()) {
      m_running = false;
    }

    if (const auto *keyPressed = event->getIf<sf::Event::KeyPressed>()) {
      
      switch (keyPressed->scancode) {
        case sf::Keyboard::Scancode::W:
          m_player->cInput->up = true;
          break;
        case sf::Keyboard::Scancode::A:
          m_player->cInput->left = true;
          break;
        case sf::Keyboard::Scancode::S:
          m_player->cInput->down = true;
          break;
        case sf::Keyboard::Scancode::D:
          m_player->cInput->right = true;
          break;
        default: break;
      }
    }

    if (const auto *keyReleased = event->getIf<sf::Event::KeyReleased>()) {

      switch (keyReleased->scancode) {
        case sf::Keyboard::Scancode::W:
          m_player->cInput->up = false;
          break;
        case sf::Keyboard::Scancode::A:
          m_player->cInput->left = false;
          break;
        case sf::Keyboard::Scancode::S:
          m_player->cInput->down = false;
          break;
        case sf::Keyboard::Scancode::D:
          m_player->cInput->right = false;
          break;
        default: break;
      }
    }

    if (const auto *mouseButtonPressed = event->getIf<sf::Event::MouseButtonPressed>()) {

      if (mouseButtonPressed->button == sf::Mouse::Button::Left) {

        spawnBullet(m_player, Vec2(mouseButtonPressed->position.x, mouseButtonPressed->position.y));
      }
    }
  }

}

void Game::sMovement() {

    m_player->cTransform->velocity = { 0, 0 };

    if (m_player->cInput->up) {

      m_player->cTransform->velocity.y = -5;
    }
    if (m_player->cInput->down) {

      m_player->cTransform->velocity.y = 5;
    }
    if (m_player->cInput->left) {

      m_player->cTransform->velocity.x = -5;
    }
    if (m_player->cInput->right) {

      m_player->cTransform->velocity.x = 5;
    }

    for (auto &e : m_entities.getEntities()) {

      if (!e->cTransform) {
        
        std::cerr << "❌ Entity with tag '" << e->tag() << "' has no CTransform!\n";
        continue;
      } 

      e->cTransform->pos.x += e->cTransform->velocity.x;
      e->cTransform->pos.y += e->cTransform->velocity.y;
    }
}

void Game::sCollision() {

  auto &entities = m_entities.getEntities();
  for (size_t i = 0; i < entities.size(); i++) {
    auto &e = entities[i];

    if (!e->cTransform || !e->cShape) continue;

    float radius = e->cShape->circle.getRadius();

    if (e->cTransform->pos.x >= m_window.getSize().x - radius) {
      e->cTransform->pos.x       = m_window.getSize().x - radius;
      e->cTransform->velocity.x *= -1.0f;
    }
    if (e->cTransform->pos.x <= radius) {
      e->cTransform->pos.x       = radius;
      e->cTransform->velocity.x *= -1.0f;
    }
    if (e->cTransform->pos.y >= m_window.getSize().y - radius) {
      e->cTransform->pos.y       = m_window.getSize().y - radius;
      e->cTransform->velocity.y *= -1.0f;
    }
    if (e->cTransform->pos.y <= radius) {
      e->cTransform->pos.y       = radius;
      e->cTransform->velocity.y *= -1.0f;
    }

    for (size_t j = i + 1; j < entities.size(); j++ ) {
      auto &a = entities[j];

      if (e == a || !a->cTransform || !a->cShape) continue;

      float dx = e->cTransform->pos.x - a->cTransform->pos.x;
      float dy = e->cTransform->pos.y - a->cTransform->pos.y;
      float distanceSq = dx * dx + dy * dy; //save performance with std::sqrt(dx * dx + dy * dy) by just multiplying combinedRadius until exact value needed

      float combinedRadius = e->cShape->circle.getRadius() + a->cShape->circle.getRadius();

      if (distanceSq <= (combinedRadius * combinedRadius) && distanceSq > 0.0f) {

        float distance = std::sqrt(distanceSq);

        if (e->tag() == "enemy" && a->tag() == "enemy") {

          Vec2 normal = (a->cTransform->pos - e->cTransform->pos) / distance;

          Vec2 relativeVelocity = e->cTransform->velocity - a->cTransform->velocity;
          float velAlongNormal  = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y;

          if (velAlongNormal > 0.0f) continue;

          std::swap(e->cTransform->velocity, a->cTransform->velocity);

          float overlap       = 0.5f * (combinedRadius - distance);
          e->cTransform->pos -= normal * overlap;
          a->cTransform->pos += normal * overlap;

          std::cout << "Enemies " << e->id() << " and " << a->id() << " bounced!\n";
        } else {
          e->destroy();
          a->destroy();
          m_entities.setDied(true);
        }
      }
    }
  }
}

void Game::sEnemySpawner() {

  /**
   * @todo spawn logic
   */
  if (m_currentFrame - m_lastEnemySpawnTime >= 200) {

    spawnEnemy();
  }

}

float Game::randFloat(float min, float max) {
  std::uniform_real_distribution<float> dist(min, max);
  return dist(m_rng);
}

int Game::randInt(int min, int max) {
  std::uniform_int_distribution<int> dist(min, max);
  return dist(m_rng);
}
