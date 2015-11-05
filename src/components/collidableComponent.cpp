#include "components/collidableComponent.h"

CollidableComponent::CollidableComponent(sf::Vector2f xy, float height, float width)
{
  this->setType(constants::COLLIDABLE);
  boundingBox = new sf::FloatRect(xy.x, xy.y, width, height);
  slideDirection = 0;
}

void CollidableComponent::moveTo(sf::Vector2f xy){
  boundingBox->left = xy.x - boundingBox->width/2;
  boundingBox->top = xy.y - boundingBox->height/2;
}
