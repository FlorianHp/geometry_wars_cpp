#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "EntityManager.h"

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig  { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };

struct Context {
  EntityManager& entities;
  sf::RenderWindow& window;
  std::vector<sf::Sound>& bounceSounds;
  std::vector<sf::Sound>& explosionSounds;  

  int  score;
  int  currentFrame;
  int  lastEnemySpawnTime;
  bool paused;
  bool running;
    
  PlayerConfig playerConfig;
  BulletConfig bulletConfig;
  EnemyConfig  enemyConfig;  
  std::shared_ptr<Entity> player;
};