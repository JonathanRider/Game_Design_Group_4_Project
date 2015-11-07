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
  enum InputCandidate {STATE_SWITCHER, PLAYER, MAINMENU, LEVELMENU, OPTIONSMENU, UNKNOWN};
  void handleKeyInput(sf::Event &e, constants::Input &input, InputCandidate &candidate);
  void handleMouseInput(sf::Event &e, constants::Input &input, InputCandidate &candidate);
  EntityManager *manager;
  sf::RenderWindow *screen;
  LevelCreator *lCreator;
};

#endif
