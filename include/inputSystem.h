#ifndef _INPUT_SYSTEM_H_
#define _INPUT_SYSTEM_H_


//need to include pretty much all components as well
#include "entityManager.h"
#include "components/controllableComponent.h"
#include "components/moveableComponent.h"
#include "constants.h"

class InputSystem
{
public:
  InputSystem(EntityManager *m, GameState state);
  ~InputSystem();
  void update(float time);
  void handleKeyPress(sf::Event e);

private:
  EntityManager* manager;
  GameState state;
};

#endif
