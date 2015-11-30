#include "components/graphicsComponent.h"
#include <cmath>
#include <iostream>

namespace{
  float computeAngle (sf::Vector2f &s, sf::Vector2f &d) {
    //compute the angle to rotate x positive axis to s->d (use clockwise)
    //use the fumular cos (A) = (a . b)/(|a||b|)
    sf::Vector2f a, b;
    a.x = d.x - s.x; a.y = d.y - s.y;
    b.x = 1; b.y = 0;
    float cos_value = (a.x * b.x + a.y * b.y)/(sqrt(pow(a.x,2)+pow(a.y,2)) * (1));
    float angle = acos(cos_value) * 180 /PI;
    if (a.y < 0 ){
      angle *= -1;
    }
    return angle;
  }
}

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
  sf::Vector2f my_position = getCenter();

  float angle = 0;
  if (position.x == position.y){
    return;
    //do I need to do something?
  }
  angle = computeAngle(my_position, position);
  angle += 90; //since the original image is not towards right, make this correction
  sprite->setRotation(angle);
}
sf::Vector2f GraphicsComponent::getCenter(){
  sf::Vector2f center_position = sprite->getPosition();
  center_position.x += sprite->getTexture()->getSize().x / 2;
  center_position.y += sprite->getTexture()->getSize().y / 2;
  return center_position;
}
