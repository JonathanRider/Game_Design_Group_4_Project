#ifndef _INPUT_SYSTEM_H_
#define _INPUT_SYSTEM_H_


//need to include pretty much all components as well
#include "entityManager.h"
#include "components/controllableComponent.h"
#include "components/moveableComponent.h"
#include "constants.h"
#include "gameState.h"

class InputSystem
{
public:
  InputSystem(EntityManager *m, GameState *state, sf::RenderWindow *w);
  ~InputSystem();
  void update(float time);
  void handleKeyPress(sf::Event e);

private:
  EntityManager *manager;
  sf::RenderWindow *screen;
  GameState *state;
};

#endif
