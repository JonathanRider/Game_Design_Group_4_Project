#ifndef _COLLIDABLE_COMPONENT_H_
#define _COLLIDABLE_COMPONENT_H_

#include "components/component.h"
#include "SFML/Graphics.hpp"

class CollidableComponent : public Component
{
public:
  CollidableComponent(sf::Vector2f xy, float height, float width);
  ~CollidableComponent(){delete boundingBox;}

  sf::FloatRect* getBoundingBox(){return boundingBox;}
  void setBoundingBox(sf::FloatRect *bb){boundingBox = bb;}

  void moveTo(sf::Vector2f xy);


private:
  sf::FloatRect *boundingBox;


};


#endif
