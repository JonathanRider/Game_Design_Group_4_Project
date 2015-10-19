#include "inputSystem.h"
#include <cmath>
#include <iostream>

InputSystem::InputSystem(EntityManager *m, GameState *s, sf::RenderWindow *w)
  :manager(m), state(s), screen(w){}

void InputSystem::update(float time){

  if (state->getGameState() == PLAYING) {
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
      // if(iterator->hasComponent(VISION)){
      //   VisionComponent *vc = (VisionComponent*) iterator->getComponent(VISION);
      //   sf::Vector2i  mp= sf::Mouse::getPosition(*screen);
      //   float dy = iterator->getXY().y - mp.y;
      //   float dx = iterator->getXY().x - mp.x;
      //   //atan2(dy, dx) * 180 / PI + 180;
      //
      //   vc->setDirection(atan2(dy, dx) * 180 / PI + 180);
      // }
    }
  }
}

void InputSystem::handleKeyPress(sf::Event e){
  if (state->getGameState() == MENU) {
    if(e.key.code == sf::Keyboard::Up) {
      std::cout << "up\n";
    } else if(e.key.code == sf::Keyboard::Down) {
      std::cout << "down\n";
    }
    else if(e.key.code == sf::Keyboard::Return) {
      state->setGameState(PLAYING);
    }
  } else if (state->getGameState() == PLAYING) {
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
        } else if(e.key.code == cp->getKey(PAUSE)){
          state->setGameState(PAUSED);
        }
      }
    }
  }else if (state->getGameState() == PAUSED) {
    if(e.key.code == sf::Keyboard::Return) {
      state->setGameState(PLAYING);
    }
  }
}
