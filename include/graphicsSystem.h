#ifndef _GRAPHICS_SYSTEM_H_
#define _GRAPHICS_SYSTEM_H_

#include "components/graphicsComponent.h"
#include "entityManager.h"
#include <SFML/Graphics.hpp>

class GraphicsSystem
{
public:
  GraphicsSystem(sf::RenderWindow* w, EntityManager *m);
  ~GraphicsSystem();
  void update(float time);
  void draw(sf::Drawable *drawable);
  void draw(void (*callback)(sf::RenderWindow* w));

private:
  sf::RenderWindow* screen;
  EntityManager* manager;
  sf::Sprite background_sprite;
  sf::Sprite pausedSprite;
};

#endif
