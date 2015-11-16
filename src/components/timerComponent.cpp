#include "timerComponent.h"

TimerComponent::TimerComponent(float t, constants::TimerEntity te)
  :time(t), timerE(te)
{
  this->setType(constants::TIMER);
}
