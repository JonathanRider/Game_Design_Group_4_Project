#ifndef _INPUT_SYSTEM_H_
#define _INPUT_SYSTEM_H_


//need to include pretty much all components as well
#include "entityManager.h"
#include "components/moveableComponent.h"



class InputSystem
{
public:
  InputSystem(EntityManager *m, sf::RenderWindow *w);
  ~InputSystem();
  void update(float time);


private:
  enum InputCandidate {STATE_SWITCHER, PLAYER, UNKNOWN};
  void handleKeyInput(sf::Event &e, constants::Input &input, InputCandidate &candidate);
  void handleMouseInput(sf::Event &e, constants::Input &input, InputCandidate &candidate);
  EntityManager *manager;
  sf::RenderWindow *screen;
};

#endif
