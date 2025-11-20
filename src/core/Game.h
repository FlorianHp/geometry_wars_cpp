#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "Entity.h"
#include "EntityManager.h"
#include "Context.h"

#include "systems/SCollisionDetection.h"
#include "systems/SCollisionResponse.h"
#include "systems/SEnemySpawner.h"
#include "systems/SMovement.h"
#include "systems/SRender.h"
#include "systems/SUserInput.h"
#include "systems/SBullet.h"
#include "systems/SExplosion.h"



class Game {

  sf::RenderWindow          m_window;
  EntityManager             m_entities;
  sf::Font                  m_font;
  sf::Text                  m_text;
  sf::SoundBuffer           m_explosionBuffer;
  sf::SoundBuffer           m_bounceBuffer;
  sf::Clock                 m_clock;
  sf::Texture               m_dummy;
  std::vector<sf::Sound>    m_bounceSounds;
  std::vector<sf::Sound>    m_explosionSounds;
  Context                   ctx;

  static constexpr int SOUND_POOL_SIZE = 8;

  void init(const std::string &config);

  //void sLifespan();
  void spawnPlayer();
  void repositionPlayer(Context& ctx);
  //void spawnSpecialWeapon(std::shared_ptr<Entity> entity);


public:

  Game(const std::string &config);

  void run();
};