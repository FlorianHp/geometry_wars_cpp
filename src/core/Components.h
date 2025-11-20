#pragma once

#include "Vec2.h"
#include <SFML/Graphics.hpp>

struct CTransform {

  Vec2 pos      = { 0.0, 0.0 };
  Vec2 velocity = { 0.0, 0.0 };
  float angle   = 0;

  CTransform(const Vec2 &p, const Vec2 &v, float a)
    : pos(p), velocity(v), angle(a) {}
};


struct CShape {
  sf::CircleShape circle;
  sf::RectangleShape rect;
  bool useRect = false;


  CShape(float radius, int points, const sf::Color &fill, sf::Color outline, float thickness)
    : circle(radius, points),
      rect(sf::Vector2f(radius * 2.f, radius * 2.f)),
      useRect(false)
  {
      circle.setFillColor(fill);
      circle.setOutlineColor(outline);
      circle.setOutlineThickness(thickness);
      circle.setOrigin(sf::Vector2f(radius, radius));

      rect.setFillColor(sf::Color::White);
      rect.setOrigin({radius, radius});
  }

  CShape(float width, float height, const sf::Color &fill)
    : circle(0.f, 0), rect(sf::Vector2f(width, height)), useRect(true)
  {
    rect.setFillColor(fill);
    rect.setOrigin({width * 0.5f, height * 0.5f});
  }
};

/* struct CCollider {
    float radius = 0.0f;
    bool isTrigger = false;

    CCollider() = default;
    CCollider(float r, bool trigger = false)
        : radius(r), isTrigger(trigger) {}
}; */

struct CScore {

  int score = 0;
  CScore(int s)
    : score(s) {}
};

struct CLifespan {

  int remaining = 0;
  int total     = 0;
  CLifespan(int total)
    : remaining(total), total(total) {}
};

struct CInput {

  bool up    = false;
  bool left  = false;
  bool right = false;
  bool down  = false;
  bool shoot = false;

  CInput() {}
};

struct COwner {

  size_t id = 0;

  COwner() = default;
  COwner(size_t ownerId)
    : id(ownerId) {}
};

struct CProjectile {

  Vec2 lastPos;
  float maxDistance = 0;
  float traveled   = 0;
  float fadeStartFactor = 0.7f;

  CProjectile() = default;

  CProjectile(const Vec2& start,
    float maxDist,
    float fadeFactor = 0.7f)
    : lastPos(start),
    maxDistance(maxDist),
    traveled(0.0f),
    fadeStartFactor(fadeFactor) {}
};

struct CDamage {
  
  int amount = 0;

  CDamage() = default;
  CDamage(int dmg) : amount(dmg) {}
};

struct CExplosion {

  float time     = 0.0f;
  float lifetime = 1.0f;
  float power    = 1.0f;
  CExplosion(float life = 1.0f, float pow = 1.0f)
    : lifetime(life), power(pow) {}
};