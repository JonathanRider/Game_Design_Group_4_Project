#ifndef _INPUT_SYSTEM_H_
#define _INPUT_SYSTEM_H_


//need to include pretty much all components as well
#include "entityManager.h"
#include "components/controllableComponent.h"
#include "components/moveableComponent.h"



class InputSystem
{
public:
  InputSystem(EntityManager *m, sf::RenderWindow *w);
  ~InputSystem();
  void update(float time);
  void handleEvent(sf::Event e);
  void handleKeyPress(sf::Event e);
  void handleClick(sf::Event e);

private:
  EntityManager *manager;
  sf::RenderWindow *screen;
};

#endif
