#ifndef _TRAP_COMPONENT_H_
#define _TRAP_COMPONENT_H_

#include "components/component.h"

class TrapComponent : public Component
{
public:

  TrapComponent(bool isVisible);
  ~TrapComponent(){};

  void changeVisibility();
  bool getVisibility(){return isVisible;}

private:

  bool isVisible;
};

#endif
