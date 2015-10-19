#ifndef _ENEMY_COMPONENT_H_
#define _ENEMY_COMPONENT_H_


#include "components/component.h"

class EnemyComponent : public Component
{
public:
  EnemyComponent(){this->setType(ENEMY);}
  ~EnemyComponent();
};

#endif
