#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "constants.h"

class Component
{
public:
  Component(){}
  Component(constants::ComponentType t){type = t;}
  virtual ~Component(){}

  constants::ComponentType getType(){return type;} //enum
  void setType(constants::ComponentType t){type = t;}


private:
  constants::ComponentType type;
};

#endif
