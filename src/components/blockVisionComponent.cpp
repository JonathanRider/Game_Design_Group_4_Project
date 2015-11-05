#include "components/blockVisionComponent.h"


BlockVisionComponent::BlockVisionComponent(sf::Vector2f xy, float h, float w)
  :height(h), width(w)
{

  top =  sf::VertexArray(sf::Lines, 2);
  left =  sf::VertexArray(sf::Lines, 2);
  right =  sf::VertexArray(sf::Lines, 2);
  bottom =  sf::VertexArray(sf::Lines, 2);

  this->setType(constants::BVISION);
  this->moveTo(xy);
}

void BlockVisionComponent::moveTo(sf::Vector2f xy){

  this->setTopLeft(sf::Vector2f(xy.x - WALLSIZE/2, xy.y - WALLSIZE/2));
  this->setTopRight(sf::Vector2f(xy.x + width-WALLSIZE/2, xy.y - WALLSIZE/2));
  this->setBottomLeft(sf::Vector2f(xy.x - WALLSIZE/2, xy.y + height-WALLSIZE/2));
  this->setBottomRight(sf::Vector2f(xy.x + width - WALLSIZE/2, xy.y + height -WALLSIZE/2));
}

void BlockVisionComponent::setTopLeft(sf::Vector2f tl){
  topLeft = tl;
  top[0].position = tl;
  left[0].position = tl;
}
void BlockVisionComponent::setTopRight(sf::Vector2f tr){
  topRight = tr;
  top[1].position = tr;
  right[0].position = tr;
}
void BlockVisionComponent::setBottomLeft(sf::Vector2f bl){
  bottomLeft = bl;
  bottom[0].position = bl;
  left[1].position = bl;
}
void BlockVisionComponent::setBottomRight(sf::Vector2f br){
  bottomRight = br;
  bottom[1].position = br;
  right[1].position = br;
}
