#include "graphicsComponent.h"
#include <iostream>

GraphicsComponent::GraphicsComponent(/*sf::Sprite*/ sf::RectangleShape* s, float a, float al)
  :sprite(s), angle(a), alpha(al)
{
  this->setType(GRAPHICS);
}
