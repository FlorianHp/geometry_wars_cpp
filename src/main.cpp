#include <SFML/Graphics.hpp>
#include "core/Game.h"

int main() {
  freopen("/dev/null", "w", stderr);
  
  Game g("data/config.txt");
  g.run();
}