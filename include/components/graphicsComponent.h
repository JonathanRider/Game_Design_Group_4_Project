#ifndef _GRAPHICS_COMPONENT_H_
#define _GRAPHICS_COMPONENT_H_

#include "components/component.h"
#include <SFML/Graphics.hpp>

class GraphicsComponent : public Component
{
public:
  GraphicsComponent(sf::Sprite* s, float a = 0, float al = 0);
  ~GraphicsComponent(){delete sprite;}

  void setGraphics(sf::Sprite);
  void setRotation(float a);
  void rotate(float a);
  void rotateTo(sf::Vector2f &position);
  float getRotation();
  void setOpacity(float a);

  sf::Sprite* getSprite(){return sprite;}

private:
  sf::Sprite* sprite;
  float angle;
  float alpha;

};


#endif
