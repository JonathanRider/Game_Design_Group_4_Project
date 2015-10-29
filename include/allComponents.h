#ifndef _ALL_COMPONENTS_H_
#define _ALL_COMPONENTS_H_


#include "components/component.h"
#include "components/controllableComponent.h"
#include "components/graphicsComponent.h"
#include "components/moveableComponent.h"
#include "components/collidableComponent.h"
#include "components/blockVisionComponent.h"
#include "components/blockMovementComponent.h"
#include "components/visionComponent.h"



//empty components

class EnemyComponent : public Component
{
public:
  EnemyComponent(){this->setType(ENEMY);}
  ~EnemyComponent();
};

class BounceProjectileComponent : public Component
{
public:
  BounceProjectileComponent(){this->setType(BOUNCEPROJECTILE);}
  ~BounceProjectileComponent();
};



#endif
