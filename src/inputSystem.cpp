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
        //std::cout << "up\n";
        sf::Vector2f v = iterator->getXY();
        iterator->setXY(sf::Vector2f(v.x, v.y - 500*time));
      }else if(sf::Keyboard::isKeyPressed(cp->getKey(DOWN))){
        //std::cout << "down\n";
        sf::Vector2f v = iterator->getXY();
        iterator->setXY(sf::Vector2f(v.x, v.y + 500*time));
      }

      if(sf::Keyboard::isKeyPressed(cp->getKey(LEFT))){
        //std::cout << "left\n";
        sf::Vector2f v = iterator->getXY();
        iterator->setXY(sf::Vector2f(v.x- 500*time, v.y));
      }else if(sf::Keyboard::isKeyPressed(cp->getKey(RIGHT))){
        //std::cout << "right\n";
        sf::Vector2f v = iterator->getXY();
        iterator->setXY(sf::Vector2f(v.x + 500*time, v.y));
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
