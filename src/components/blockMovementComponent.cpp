#include "components/blockMovementComponent.h"

BlockMovementComponent::BlockMovementComponent(sf::Vector2f xy, float height, float width)
  :CollidableComponent(xy, height, width)
{
  this->setType(constants::BMOVEMENT);
  boundingBox = new sf::FloatRect(xy.x-WALLSIZE/2, xy.y-WALLSIZE/2, width, height);

}
