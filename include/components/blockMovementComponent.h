#ifndef _BLOCK_MOVEMENT_H_
#define _BLOCK_MOVEMENT_H_

#include "components/collidableComponent.h"
#include "SFML/Graphics.hpp"

class BlockMovementComponent : public CollidableComponent
{
public:
  BlockMovementComponent(sf::Vector2f xy, float height, float width);
  ~BlockMovementComponent(){}
};


#endif
