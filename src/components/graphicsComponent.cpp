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
  if (my_position == position){
    return;
    //do I need to do something?
  }
  else if (my_position.x == position.x ){
    std::cout << "X=X" <<std::endl;
    angle = my_position.y < position.y?90:-90;
  }
  else if (my_position.y == position.y){
    angle = my_position.x < position.x?0:180;
  }
  else {
    //std::cout <<(position.y - my_position.y)/(position.x - position.x)<< std::endl;
    angle = atan((position.y - my_position.y)/(position.x - my_position.x))*180/PI;
  }
  angle += 90;
  std::cout << "Roate angle = " << angle << std::endl;
  sprite->setRotation(angle);
}
