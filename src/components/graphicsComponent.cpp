#include "components/graphicsComponent.h"
#include <iostream>

GraphicsComponent::GraphicsComponent(sf::Sprite* s, float a, float al)
  :sprite(s), angle(a), alpha(al)
{
  this->setType(constants::GRAPHICS);
}
