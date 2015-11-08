#ifndef _COLLIDABLE_COMPONENT_H_
#define _COLLIDABLE_COMPONENT_H_

#include "components/component.h"
#include "SFML/Graphics.hpp"

class CollidableComponent : public Component
{
public:
  CollidableComponent(sf::Vector2f xy);
  ~CollidableComponent(){}


  void setSlideDirection(int s){slideDirection = s;}
  int getSlideDirection(){return slideDirection;}


protected:
  int slideDirection;  //-1:y, 0 none, 1:x. Used to prevent sticking on walls when sliding along them
};


#endif
