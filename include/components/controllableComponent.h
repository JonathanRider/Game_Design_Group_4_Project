#ifndef _MOVEABLE_COMPONENT_H_
#define _MOVEABLE_COMPONENT_H_

#include "components/component.h"
#include "constants.h"
#include <SFML/Window/Keyboard.hpp>

class ControllableComponent : public Component
{
public:

  ControllableComponent(bool active = true, sf::Keyboard::Key up = sf::Keyboard::Up ,
                        sf::Keyboard::Key down = sf::Keyboard::Down ,
                        sf::Keyboard::Key left = sf::Keyboard::Left ,
                        sf::Keyboard::Key right = sf::Keyboard::Right ,
                        sf::Keyboard::Key item = sf::Keyboard::F ,
                        sf::Keyboard::Key use = sf::Keyboard::R ,
                        sf::Keyboard::Key next = sf::Keyboard::E ,
                        sf::Keyboard::Key prev = sf::Keyboard::Q);
  ~ControllableComponent();

  void changeKey(Input i, sf::Keyboard::Key newKey);
  sf::Keyboard::Key getKey(Input i);





private:
  bool isActive;
  sf::Keyboard::Key upKey;
  sf::Keyboard::Key downKey;
  sf::Keyboard::Key leftKey;
  sf::Keyboard::Key rightKey;
  sf::Keyboard::Key itemKey;
  sf::Keyboard::Key useKey;
  sf::Keyboard::Key nextItemKey;
  sf::Keyboard::Key prevItemKey;

};


#endif
