#include "components/collidableComponent.h"

CollidableComponent::CollidableComponent(sf::Vector2f xy, float height, float width)
{
  this->setType(COLLIDABLE);
  boundingBox = new sf::FloatRect(xy.x - width/2, xy.y - height/2, width, height);
}

void CollidableComponent::moveTo(sf::Vector2f xy){
  boundingBox->left = xy.x - boundingBox->width/2;
  boundingBox->top = xy.y - boundingBox->height/2;
}
