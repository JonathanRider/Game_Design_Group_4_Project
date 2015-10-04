#ifndef _MOVEABLE_COMPONENT_H_
#define _MOVEABLE_COMPONENT_H_

#include "component.h"

class GraphicsComponent : public Component
{
public:
  GraphicsComponent(int speed);
  ~GraphicsComponent();

  void setSpeed(int s);
  int getSpeed();
  void setDirectoin(float d);
  int




private:
  int speed;
  float direction;

};


#endif
