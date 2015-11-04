#include "inputSystem.h"
#include "global.h"
#include <cmath>
#include <iostream>

InputSystem::InputSystem(EntityManager *m, sf::RenderWindow *w)
  :manager(m), screen(w){}

void InputSystem::update(float time){

  if (global()->gameEngine.gameState == constants::PLAYING) {
    std::list<Entity*>* eList = manager->getEntityList();
    std::list<Entity*>::iterator iterator;
    for (iterator = eList->begin(); iterator != eList->end(); ++iterator) {
      if((*iterator)->hasComponent(constants::CONTROLLABLE)){
        ControllableComponent *cp = (ControllableComponent*)(*iterator)->getComponent(constants::CONTROLLABLE);
        if((*iterator)->hasComponent(constants::MOVEABLE)){
          MoveableComponent *mp = (MoveableComponent*)(*iterator)->getComponent(constants::MOVEABLE);
          if(sf::Keyboard::isKeyPressed(cp->getKey(constants::UP))){
              if(sf::Keyboard::isKeyPressed(cp->getKey(constants::LEFT))){
                mp->setDirection(135.0);
              }else if(sf::Keyboard::isKeyPressed(cp->getKey(constants::RIGHT))){
                mp->setDirection(45.0);
              }else{
                mp->setDirection(90.0);
              }
              mp->setAccelerating(true);
          }else if(sf::Keyboard::isKeyPressed(cp->getKey(constants::DOWN))){
            if(sf::Keyboard::isKeyPressed(cp->getKey(constants::LEFT))){
              mp->setDirection(225.0);
            }else if(sf::Keyboard::isKeyPressed(cp->getKey(constants::RIGHT))){
              mp->setDirection(315.0);
            }else{
              mp->setDirection(270.0);
            }
            mp->setAccelerating(true);
          }else if(sf::Keyboard::isKeyPressed(cp->getKey(constants::LEFT))){
            mp->setDirection(180.0);
            mp->setAccelerating(true);
          }else if(sf::Keyboard::isKeyPressed(cp->getKey(constants::RIGHT))){
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
void InputSystem::handleEvent(sf::Event e){

}
void InputSystem::handleKeyPress(sf::Event e){
  if (global()->gameEngine.gameState == constants::MENU) {
    if(e.key.code == sf::Keyboard::Up) {
      std::cout << "up\n";
    } else if(e.key.code == sf::Keyboard::Down) {
      std::cout << "down\n";
    }
    else if(e.key.code == sf::Keyboard::Return) {
      global()->gameEngine.gameState = constants::PLAYING;
    }
  } else if (global()->gameEngine.gameState == constants::PLAYING) {
    std::list<Entity*>* eList = manager->getEntityList();
    std::list<Entity*>::iterator iterator;
    for (iterator = eList->begin(); iterator != eList->end(); ++iterator) {
      if((*iterator)->hasComponent(constants::CONTROLLABLE)){
        ControllableComponent *cp = (ControllableComponent*)(*iterator)->getComponent(constants::CONTROLLABLE);
        if(e.key.code == cp->getKey(constants::USE)){
          std::cout << "use\n";
        }else if(e.key.code == cp->getKey(constants::ITEM)){
          std::cout << "item\n";
        }else if(e.key.code == cp->getKey(constants::NEXTITEM)){
          std::cout << "nextItem\n";
        }else if(e.key.code == cp->getKey(constants::PREVITEM)){
          std::cout << "prev item\n";
        } else if(e.key.code == cp->getKey(constants::PAUSE)){
          global()->gameEngine.gameState = constants::PAUSED;
        }
      }
    }
  }else if (global()->gameEngine.gameState == constants::PAUSED) {
    if(e.key.code == sf::Keyboard::Return) {
      global()->gameEngine.gameState = constants::PLAYING;
    }
  }
}

void InputSystem::handleClick(sf::Event e){

  //needs access to entity creator work

  // if (e.mouseButton.button == sf::Mouse::Left){
  //
  //
  //   float dy = entityM->getPlayer()->getXY().y - e.mouseButton.y;
  //   float dx = entityM->getPlayer()->getXY().x - e.mouseButton.x;
  //   float direction =  180 - atan2(dy, dx) * 180 / PI;
  //   eCreator->createGrenade(entityM->getPlayer()->getXY(), direction, 1000, 500, tex_bullet);
  //
  //
  //
  // }

}
