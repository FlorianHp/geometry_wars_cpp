#pragma once

#include "Entity.h"
#include "EntityManager.h"

#include <SFML/Graphics.hpp>
#include <random>

struct PlayerConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V; float S; };
struct EnemyConfig  { int SR, CR, OR, OG, OB, OT, VMIN, VMAX, L, SI; float SMIN, SMAX; };
struct BulletConfig { int SR, CR, FR, FG, FB, OR, OG, OB, OT, V, L; float S; };

class Game {

  sf::RenderWindow   m_window;
  EntityManager      m_entities;
  sf::Font           m_font;
  sf::Text           m_text;
  PlayerConfig       m_playerConfig;
  EnemyConfig        m_enemyConfig;
  BulletConfig       m_bulletConfig;
  std::random_device m_random;
  std::mt19937       m_rng;
  int                m_score               = 0;
  int                m_currentFrame        = 0;
  int                m_lastEnemySpawnTime  = 0;
  bool               m_paused              = false;
  bool               m_running             = true;
  bool               m_entityDied          = false;

  std::shared_ptr<Entity> m_player;

  void init(const std::string &config);
  void setPaused(bool paused);

  void sMovement();
  void sUserInput();
  void sLifespan();
  void sRender();
  void sEnemySpawner();
  void sCollision();

  void spawnPlayer();
  void spawnEnemy();
  void spawnBullet(std::shared_ptr<Entity> entity, const Vec2 &target);
  void spawnSmallEnemies(std::shared_ptr<Entity> entity);
  //void spawnSpecialWeapon(std::shared_ptr<Entity> entity);

  float randFloat(float min, float max);
  int randInt(int min, int max);

  public:

    Game(const std::string &config);

    void run();
};