#ifndef _MOVEABLE_COMPONENT_H_
#define _MOVEABLE_COMPONENT_H_

#include "components/component.h"

class MoveableComponent : public Component
{
public:
  MoveableComponent(float a, float dec, float ms, float s = 0, float d = 0, float x = 9, float y = 0, float minx = 0, float miny = 0);
  ~MoveableComponent(){}

  void changeVelocity(float v);
  void setVelocity(float v){velocity = v;}
  float getVelocity(){return velocity;}
  void setAcceleration(float a){acceleration = a;}
  float getAcceleration(){return acceleration;}
  void setDeceleration(float d){deceleration = d;}
  float getDeceleration(){return deceleration;}
  void setDirection(float d){direction = d;}
  float getDirection(){return direction;}
  float getMaxXPos(){return maxXPos;}
  void setMaxXPos(float x){maxXPos = x;}
  float getMaxYPos(){return maxYPos;}
  void setMaxYPos(float y){maxYPos = y;}
  float getMinXPos(){return minXPos;}
  void setMinXPos(float x){minXPos = x;}
  float getMinYPos(){return minYPos;}
  void setMinYPos(float y){minYPos = y;}

  void setAccelerating(bool a){accelerating =a;}
  bool getAccelerating(){return accelerating;}


  void setMaxVelocity(float s){maxVelocity = s;}
  float getMaxVelocity(){return maxVelocity;}




private:
  float velocity;
  float acceleration;
  float deceleration;
  float maxVelocity;
  float direction;
  bool accelerating;
  float maxXPos;
  float maxYPos;
  float minXPos;
  float minYPos;


};


#endif
