#include "components/collidableComponent.h"

CollidableComponent::CollidableComponent(sf::Vector2f xy)
{
  this->setType(constants::COLLIDABLE);
  slideDirection = 0;
}
