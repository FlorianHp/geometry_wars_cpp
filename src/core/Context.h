#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "EntityManager.h"

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig  { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };

struct Context {

  EntityManager&          entities;
  sf::RenderWindow&       window;
  std::vector<sf::Sound>& bounceSounds;
  std::vector<sf::Sound>& explosionSounds;

  std::unique_ptr<sf::Text> scoreText;
  sf::Clock   clock;
  int         score              = 0;
  int         currentFrame       = 0;
  int         lastEnemySpawnTime = 0;
  bool        paused             = false;
  bool        running            = true;
  bool        debug              = false;

  PlayerConfig playerConfig{};
  BulletConfig bulletConfig{};
  EnemyConfig  enemyConfig{};

  std::shared_ptr<sf::Texture> dummyTexture;
  std::shared_ptr<sf::Shader>  bulletShader;
  std::shared_ptr<sf::Shader>  explosionShader;
  std::shared_ptr<Entity>      player;

  Context(
    EntityManager& e,
    sf::RenderWindow& w,
    std::vector<sf::Sound>& bounce,
    std::vector<sf::Sound>& explode
    )
    : entities(e)
    , window(w)
    , bounceSounds(bounce)
    , explosionSounds(explode) {}
};