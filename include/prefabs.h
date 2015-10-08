#ifndef _PREFABS_H_
#define _PREFABS_H_

#include "allComponents.h"
#include "SFML/Graphics.hpp"
#include "entity.h"

namespace prefabs
{
  extern int curID;
  extern int getNewID();

  extern Entity* newPlayer(float x, float y);
  extern sf::Texture *playerTexture;

  extern Entity* newWall(float x, float y);
  extern sf::Texture *wallTexture;
}

#endif
