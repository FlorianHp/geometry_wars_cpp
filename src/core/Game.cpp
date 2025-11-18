#include "Game.h"

#include <iostream>
#include <fstream>
#include <random>
#include <SFML/Graphics.hpp>


Game::Game(const std::string &config)
: m_text(m_font, "", 24),
  ctx{ m_entities, m_window, m_bounceSounds, m_explosionSounds, 0, 0, 0, false, true, false } {
  init(config);
}

void Game::init(const std::string &path) {
  

  if (!m_font.openFromFile("assets/fonts/Asimovian-Regular.ttf")) {
    std::cerr << "Error loading font" << std::endl;
  }

  if (!m_explosionBuffer.loadFromFile("assets/sounds/explosion.wav")) {
    
    std::cerr << "Error loading explosion.wav\n";
  }
  if (!m_bounceBuffer.loadFromFile("assets/sounds/bounce.wav")) {

    std::cerr << "Error loading bounce.wav\n";
  }
  /* if (!m_shootBuffer.loadFromFile("shoot.wav")) {

    std::cerr << "Error loading shoot.wav\n";
  } */

  ctx.bounceSounds.reserve(SOUND_POOL_SIZE);
  ctx.explosionSounds.reserve(SOUND_POOL_SIZE);

  for (int i = 0; i < SOUND_POOL_SIZE; ++i) {
      ctx.bounceSounds.emplace_back(m_bounceBuffer);
      ctx.explosionSounds.emplace_back(m_explosionBuffer);
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

      ctx.window.create(sf::VideoMode({width, height}),
        "Geometry War",
        sf::Style::Default,
        sf::State::Windowed
      );
      
      ctx.window.setFramerateLimit(frameLimit);
    }

    else if (type == "Player") {
      fin >> ctx.playerConfig.SR
          >> ctx.playerConfig.CR
          >> ctx.playerConfig.S
          >> ctx.playerConfig.FR >> ctx.playerConfig.FG >> ctx.playerConfig.FB
          >> ctx.playerConfig.OR >> ctx.playerConfig.OG >> ctx.playerConfig.OB
          >> ctx.playerConfig.OT 
          >> ctx.playerConfig.V;
    }

    else if (type == "Enemy") {
      fin >> ctx.enemyConfig.SR 
          >> ctx.enemyConfig.CR
          >> ctx.enemyConfig.SMIN >> ctx.enemyConfig.SMAX
          >> ctx.enemyConfig.OR >> ctx.enemyConfig.OG >> ctx.enemyConfig.OB
          >> ctx.enemyConfig.OT
          >> ctx.enemyConfig.VMIN >> ctx.enemyConfig.VMAX
          >> ctx.enemyConfig.L 
          >> ctx.enemyConfig.SI;
    }

    else if (type == "Bullet") {
      fin >> ctx.bulletConfig.SR 
          >> ctx.bulletConfig.CR
          >> ctx.bulletConfig.S
          >> ctx.bulletConfig.FR >> ctx.bulletConfig.FG >> ctx.bulletConfig.FB
          >> ctx.bulletConfig.OR >> ctx.bulletConfig.OG >> ctx.bulletConfig.OB
          >> ctx.bulletConfig.OT 
          >> ctx.bulletConfig.V
          >> ctx.bulletConfig.L;
    }
  }

  fin.close();
  spawnPlayer();
}

void Game::run() {

  while(ctx.running) {

    ctx.entities.update();
    ctx.entities.entityDied = false;

    SUserInput::update(ctx);

    if (!ctx.paused) {

      SEnemySpawner::update(ctx);
      SMovement::update(ctx);
      SBullet::update(ctx);

      auto contacts = SCollisionDetection::compute(ctx);
      SCollisionResponse::resolve(ctx, contacts);
      SCollisionResponse::resolveWallCollisions(ctx);

      if ( !ctx.player || !ctx.player->isActive() ) {
        repositionPlayer(ctx);
      }
    }

    SRender::update(ctx);

    ctx.currentFrame++;
  }

}

void Game::spawnPlayer() {

  auto entity = m_entities.addEntity("player");
  
  entity->cTransform = std::make_shared<CTransform>(Vec2(m_window.getSize().x / 2, m_window.getSize().y / 2), Vec2(1.0f, 1.0f), 0.0f);

  entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(0, 0, 255), 4.0f);

  entity->cInput = std::make_shared<CInput>();

  ctx.player = entity;
}

void Game::repositionPlayer(Context& ctx) {
  
    ctx.player->cTransform->pos      = Vec2(ctx.window.getSize().x / 2, ctx.window.getSize().y / 2);
    ctx.player->cTransform->velocity = Vec2(0, 0);
    ctx.player->reactivate();
}
