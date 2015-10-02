#ifndef _GRAPHICS_SYSTEM_H_
#define _GRAPHICS_SYSTEM_H_

#include "graphicsComponent.h"
#include "entityManager.h"
#include <SFML/Graphics.hpp>

class graphicsSystem
{
public:
  graphicsSystem(sf::RenderWindow* w, entityManager *m, int vType);
  ~graphicsSystem();
  void update(float time);
  void changeViewType(int v);

private:
  sf::RenderWindow* screen;
  entityManager* manager;
  int viewType;
};

#endif
