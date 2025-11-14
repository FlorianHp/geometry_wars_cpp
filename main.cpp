#include <SFML/Graphics.hpp>
#include "Game.h"

int main() {
  freopen("/dev/null", "w", stderr);
  
  Game g("config.txt");
  g.run();
}