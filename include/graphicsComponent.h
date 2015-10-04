#ifndef _GRAPHICS_COMPONENT_H_
#define _GRAPHICS_COMPONENT_H_

#include "component.h"
#include <SFML/Graphics.hpp>

class GraphicsComponent : public Component
{
public:
  GraphicsComponent(sf::Sprite* s, float a = 0, float al = 0);
  ~GraphicsComponent();

  void setGraphics(sf::Sprite);
  void setRotation(float a);
  void rotate(float a);
  float getRotation();
  void setOpacity(float a);

  sf::Sprite* getSprite(){return sprite;}

private:
  sf::Sprite* sprite;
  float angle;
  float alpha;

};


#endif
