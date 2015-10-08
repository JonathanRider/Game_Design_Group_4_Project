#include "inputSystem.h"

#include <iostream>

InputSystem::InputSystem(EntityManager *m, GameState s)
  :manager(m), state(s){}

void InputSystem::update(float time){


  std::list<Entity>* eList = manager->getEntityList();
  std::list<Entity>::iterator iterator;
  for (iterator = eList->begin(); iterator != eList->end(); ++iterator) {
    if(iterator->hasComponent(CONTROLLABLE)){
      ControllableComponent *cp = (ControllableComponent*)iterator->getComponent(CONTROLLABLE);
      if(iterator->hasComponent(MOVEABLE)){
        MoveableComponent *mp = (MoveableComponent*)iterator->getComponent(MOVEABLE);

        if(sf::Keyboard::isKeyPressed(cp->getKey(UP))){
            if(sf::Keyboard::isKeyPressed(cp->getKey(LEFT))){
              mp->setDirection(135.0);
            }else if(sf::Keyboard::isKeyPressed(cp->getKey(RIGHT))){
              mp->setDirection(45.0);
            }else{
              mp->setDirection(90.0);
            }
            mp->setAccelerating(true);
        }else if(sf::Keyboard::isKeyPressed(cp->getKey(DOWN))){
          if(sf::Keyboard::isKeyPressed(cp->getKey(LEFT))){
            mp->setDirection(225.0);
          }else if(sf::Keyboard::isKeyPressed(cp->getKey(RIGHT))){
            mp->setDirection(315.0);
          }else{
            mp->setDirection(270.0);
          }
          mp->setAccelerating(true);
        }else if(sf::Keyboard::isKeyPressed(cp->getKey(LEFT))){
          mp->setDirection(180.0);
          mp->setAccelerating(true);
        }else if(sf::Keyboard::isKeyPressed(cp->getKey(RIGHT))){
          mp->setDirection(0.0);
          mp->setAccelerating(true);
        }else{
          mp->setAccelerating(false);
        }
      }
    }
  }
}

void InputSystem::handleKeyPress(sf::Event e){

  std::list<Entity>* eList = manager->getEntityList();
  std::list<Entity>::iterator iterator;
  for (iterator = eList->begin(); iterator != eList->end(); ++iterator) {
    if(iterator->hasComponent(CONTROLLABLE)){
      ControllableComponent *cp = (ControllableComponent*)iterator->getComponent(CONTROLLABLE);
      if(e.key.code == cp->getKey(USE)){
        std::cout << "use\n";
      }else if(e.key.code == cp->getKey(ITEM)){
        std::cout << "item\n";
      }else if(e.key.code == cp->getKey(NEXTITEM)){
        std::cout << "nextItem\n";
      }else if(e.key.code == cp->getKey(PREVITEM)){
        std::cout << "prev item\n";
      }



    }
  }

}
