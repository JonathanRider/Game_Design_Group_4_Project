#ifndef _ALL_COMPONENTS_H_
#define _ALL_COMPONENTS_H_


#include "components/component.h"
#include "components/graphicsComponent.h"
#include "components/moveableComponent.h"
#include "components/collidableComponent.h"
#include "components/blockVisionComponent.h"
#include "components/visionComponent.h"
#include "components/timerComponent.h"
#include "components/trapComponent.h"
#include "components/inventoryComponent.h"
#include "components/platformingComponent.h"

//Here follows some simple components (not enough to use a single file)
class PlayerComponent : public Component{
public:
  PlayerComponent(){this->setType(constants::PLAYERC);};
  ~PlayerComponent(){}
};

#endif
