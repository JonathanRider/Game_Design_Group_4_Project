#include "components/graphicsComponent.h"
#include <cmath>
#include <iostream>

GraphicsComponent::GraphicsComponent(sf::Sprite* s, float a, float al)
  :sprite(s), angle(a), alpha(al)
{
  this->setType(constants::GRAPHICS);
}
void GraphicsComponent::setRotation(float a){
  sprite->setRotation(-a);
}
void GraphicsComponent::rotate(float a){
  sprite->rotate(-a);
}
void GraphicsComponent::rotateTo(sf::Vector2f &position){
  sf::Vector2f my_position = sprite->getPosition();
  //std::cout << my_position.x <<"," <<my_position.y <<"   "<<position.x <<"," <<position.y <<std::endl;
  float angle = 0;
  if (400 == position.x && 300 == position.y){
    return;
    //do I need to do something?
  }
  else if (400 == position.x ){
    angle = 300 < position.y?0:180;
  }
  else if (300 == position.y){
    angle = 400 < position.x?270:90;
  }
  else {
    angle = -1*atan2((position.x - 400), (position.y - 300))*180/PI;
  }
  angle += 180;
  sprite->setRotation(angle);
}
