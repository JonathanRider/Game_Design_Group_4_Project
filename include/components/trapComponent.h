#ifndef _TRAP_COMPONENT_H_
#define _TRAP_COMPONENT_H_

#include "components/component.h"

class TrapComponent : public Component
{
public:

  TrapComponent(bool isVisible, float t);
  ~TrapComponent(){};

  void changeVisibility();
  bool getVisibility(){return isVisible;}

  float getTime(){return time;}
  void setTime(float t){time = t;}

private:

  bool isVisible;
  float time;
};

#endif
