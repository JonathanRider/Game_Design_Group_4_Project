#ifndef _MOVEABLE_COMPONENT_H_
#define _MOVEABLE_COMPONENT_H_

#include "components/component.h"

class MoveableComponent : public Component
{
public:
  MoveableComponent(float a, float ms, float s = 0, float d = 0);
  ~MoveableComponent();

  void changeVelocity(float v);
  void setVelocity(float v){velocity = v;}
  float getVelocity(){return velocity;}
  void setAcceleration(float a){acceleration = a;}
  float getAcceleration(float a){return acceleration;}
  void setDirectoin(float d){direction = d;}
  float getDirection(){return direction;}

  void setAccelerating(bool a){accelerating =a;}
  bool getAccelerating(){return accelerating;}


  void setMaxVelocity(float s){maxVelocity = s;}
  float getMaxVelocity(){return maxVelocity;}




private:
  float velocity;
  float acceleration;
  float maxVelocity;
  float direction;
  bool accelerating;


};


#endif
