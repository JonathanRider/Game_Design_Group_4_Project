#ifndef _PLATFORMING_COMPONENT_H_
#define _PLATFORMING_COMPONENT_H_

#include "components/component.h"

class PlatformingComponent : public Component
{
public:

  PlatformingComponent(float ms): maxSpeed(ms), jump(true), ySpeed(0), xSpeed(0){this->setType(constants::PLATFORMING);}
  ~PlatformingComponent(){}

  bool hasJump(){return jump;}
  void setJump(bool j){jump = j;}

  void setActualDirection(float d){actualDirection = d;}
  float getActualDirection(){return actualDirection;}

  void setMaxSpeed(float s){maxSpeed = s;}
  float getMaxSpeed(){return maxSpeed;}
  void setXSpeed(float s){xSpeed = s;}
  float getXSpeed(){return xSpeed;}
  void setYSpeed(float s){ySpeed = s;}
  float getYSpeed(){return ySpeed;}


private:
  float maxSpeed;
  bool jump;
  float ySpeed;
  float xSpeed;
  float actualDirection;
};

#endif
