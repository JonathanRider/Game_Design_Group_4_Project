#include "components/visionComponent.h"
#include <iostream>

VisionComponent::VisionComponent(sf::Vector2f location, float l, float dir, float a, float minRAngle, float maxRAngle)
:xy(location), length(l), direction(dir), coneAngle(a), minRotateAngle(minRAngle), maxRotateAngle(maxRAngle)
{
  this->setType(constants::VISION);
  alert = false;
  visionResolution = 5;

  rotateDirection = 1;

  triFan = new sf::VertexArray(sf::TrianglesFan, 1 + coneAngle/this->getVisionResolution());
}

void VisionComponent::rotate(float time){
  if(minRotateAngle == maxRotateAngle){
    return;
  }
  this->setDirection(this->getDirection() + rotateDirection*20*time);


  if(this->getRotateDirection() > 0 && this->getMaxRotateAngle() < this->getDirection()){
    this->setDirection(this->getMaxRotateAngle());
    this->setRotateDirection(this->getRotateDirection()*-1);
  }else if(this->getRotateDirection() < 0 && this->getMinRotateAngle() > this->getDirection()){
    this->setDirection(this->getMinRotateAngle());
    this->setRotateDirection(this->getRotateDirection()*-1);
  }
}
