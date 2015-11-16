#ifndef _TIMER_COMPONENT_H_
#define _TIMER_COMPONENT_H_

#include "components/component.h"
#include "SFML/Graphics.hpp"

class TimerComponent : public Component
{
public:
  TimerComponent(float t, constants::TimerEntity te);
  ~TimerComponent(){}


  float getTime() {return time;}
  void setTime(float t){time = t;}
  void updateTime(float t){time = time - t;}

  constants::TimerEntity getTimerEntity(){return timerE;}





protected:
  float time;
  constants::TimerEntity timerE;
};


#endif
