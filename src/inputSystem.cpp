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

      if(sf::Keyboard::isKeyPressed(cp->getKey(UP))){
        std::cout << "up\n";
      }else if(sf::Keyboard::isKeyPressed(cp->getKey(DOWN))){
        std::cout << "down\n";
      }

      if(sf::Keyboard::isKeyPressed(cp->getKey(LEFT))){
        std::cout << "left\n";
      }else if(sf::Keyboard::isKeyPressed(cp->getKey(RIGHT))){
        std::cout << "right\n";
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
