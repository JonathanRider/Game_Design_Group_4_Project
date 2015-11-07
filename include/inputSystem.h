#ifndef _INPUT_SYSTEM_H_
#define _INPUT_SYSTEM_H_


//need to include pretty much all components as well
#include "entityManager.h"
#include "levelCreator.h"
#include "components/moveableComponent.h"



class InputSystem
{
public:
  InputSystem(EntityManager *m, sf::RenderWindow *w, LevelCreator *lc);
  ~InputSystem();
  void update(float time);


private:
  constants::Input interprertForPlayer(unsigned long input);
  constants::Input interpretForLogicSystem(unsigned long input);
  unsigned long getKeyInput();
  unsigned long getMouseInput(sf::Vector2f &position);


  constants::Input interpretForMenu(unsigned long input);
  void handleMenu(constants::Input input);

  EntityManager *manager;
  sf::RenderWindow *screen;
  LevelCreator *lCreator;
};

#endif
