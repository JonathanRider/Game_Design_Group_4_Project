#include "trapComponent.h"

TrapComponent::TrapComponent(bool isVisible, float t): isVisible(isVisible), time(t)
{
  this->setType(constants::TRAPC);
}

void TrapComponent::changeVisibility() {
  if (isVisible) {
    isVisible = false;
  } else {
    isVisible = true;
  }
}
