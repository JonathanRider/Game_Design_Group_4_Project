#include "components/moveableComponent.h"

MoveableComponent::MoveableComponent(float a, float dec, float ms, float s, float d)
  :acceleration(a), deceleration(dec), maxVelocity(ms), velocity(s), direction(d){
    this->setType(MOVEABLE);
  }

void MoveableComponent::changeVelocity(float v){
  velocity += v;
  if(velocity > maxVelocity){
    velocity = maxVelocity;
  }else if(velocity < 0 ){
    velocity = 0;
  }
}
