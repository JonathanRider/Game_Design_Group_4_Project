#include "trapComponent.h"

TrapComponent::TrapComponent(bool isVisible): isVisible(isVisible)
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
