#include "graphicsComponent.h"
#include <iostream>

graphicsComponent::graphicsComponent(/*sf::Sprite*/ sf::RectangleShape* s, float a, float al)
  :sprite(s), angle(a), alpha(al)
{
  this->setType(1);
}
