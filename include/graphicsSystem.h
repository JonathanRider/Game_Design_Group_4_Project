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

private:
  sf::RenderWindow* screen;
  EntityManager* manager;
  std::vector<sf::Texture*> menuTextures; //should be moved later
  std::vector<sf::Sprite*> mainMenuSprites;
  std::vector<sf::Sprite*> levelMenuSprites;
  sf::Sprite* gameOverSprite;
  sf::Sprite* winSprite;
};

#endif
