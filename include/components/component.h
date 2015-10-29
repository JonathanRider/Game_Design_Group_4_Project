#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "constants.h"

class Component
{
public:
  Component(){}
  Component(ComponentType t){type = t;}
  virtual ~Component(){}

  ComponentType getType(){return type;} //enum
  void setType(ComponentType t){type = t;}


private:
  ComponentType type;
};

#endif
