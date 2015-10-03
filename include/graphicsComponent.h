#ifndef _GRAPHICS_COMPONENT_H_
#define _GRAPHICS_COMPONENT_H_

#include "component.h"
#include <SFML/Graphics.hpp>

class GraphicsComponent : public Component
{
public:
  GraphicsComponent(/*sf::Sprite*/sf::RectangleShape* s, float a = 0, float al = 0);
  ~GraphicsComponent();

  void setGraphics(sf::RectangleShape);//Sprite);
  void setRotation(float a);
  void rotate(float a);
  float getRotation();
  void setOpacity(float a);

  sf::RectangleShape* getSprite(){return sprite;}

private:
  sf::RectangleShape *sprite;//sf::Sprite sprite;
  float angle;
  float alpha;

};


#endif
