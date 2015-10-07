#ifndef _GRAPHICS_SYSTEM_H_
#define _GRAPHICS_SYSTEM_H_

#include "components/graphicsComponent.h"
#include "entityManager.h"
#include "constants.h"
#include <SFML/Graphics.hpp>

class GraphicsSystem
{
public:
  GraphicsSystem(sf::RenderWindow* w, EntityManager *m, GameState state);
  ~GraphicsSystem();
  void update(float time);
  void changeViewType(GameState state);

private:
  sf::RenderWindow* screen;
  EntityManager* manager;
  GameState state;
};

#endif
