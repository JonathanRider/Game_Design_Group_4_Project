#include "components/blockMovementComponent.h"

BlockMovementComponent::BlockMovementComponent(sf::Vector2f xy, float height, float width)
  :CollidableComponent(xy, height, width)
{
  this->setType(constants::BMOVEMENT);

}
