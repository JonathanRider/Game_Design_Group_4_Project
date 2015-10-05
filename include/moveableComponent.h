#ifndef _MOVEABLE_COMPONENT_H_
#define _MOVEABLE_COMPONENT_H_

#include "component.h"

class MoveableComponent : public Component
{
public:
  MoveableComponent(int speed);
  ~MoveableComponent();

  void setSpeed(int s);
  int getSpeed();
  void setDirectoin(float d);
  float getDirection();

  void setMaxSpeed();
  int getMaxSpeed();




private:
  int speed;
  int maxSpeed;
  float direction;

};


#endif
