#include "components/moveableComponent.h"

MoveableComponent::MoveableComponent(float a, float ms, float s, float d)
  :acceleration(a), maxVelocity(ms), velocity(s), direction(d){}

void MoveableComponent::changeVelocity(float v){
  velocity += v;
  if(velocity > maxVelocity){
    velocity = maxVelocity;
  }else if(velocity < 0 ){
    velocity = 0;
  }
}
