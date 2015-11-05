#include "inputSystem.h"
#include "global.h"
#include <cmath>
#include <iostream>


InputSystem::InputSystem(EntityManager *m, sf::RenderWindow *w)
  :manager(m), screen(w){}

void InputSystem::update(float time){

  sf::Event event;
  //get the event
  screen->pollEvent(event);



  if(event.type == sf::Event::Closed ) {
    //we should shut down the game now..
    global()->gameEngine.gameState = constants::CLOSING;
    return;
  }

  constants::Input input;
  InputCandidate candidate = UNKNOWN;

  if (event.type == sf::Event::KeyPressed) {
       handleKeyInput(event, input, candidate);
  }
   else if (event.type == sf::Event::MouseButtonPressed) {
     handleMouseInput(event, input, candidate);
   }


   switch (candidate) {
     case PLAYER:
      manager->getPlayer()->receiveInput(input);//pass the input to the player
      break;
    case STATE_SWITCHER:
      //
      break;
     default:
      //do nothing
      break;
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
/*

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

}*/
void InputSystem::handleKeyInput(sf::Event &e,  constants::Input &input, InputCandidate &candidate){
  //if there is any user setting for keys, it should be implemented here
  if (global()->gameEngine.gameState == constants::MENU) {
    switch(e.key.code){
      case sf::Keyboard::Up:
        input = constants::INPUT_PREVITEM;
        //candidate = ?;
        return;
      case sf::Keyboard::Down:
        input = constants::INPUT_NEXTITEM;
        //candidate = ?;
        return;
      case sf::Keyboard::Return:
        input = constants::INPUT_CONFIRM;
        //candidate = ?;
        return;
      default:
        input = constants::INPUT_UNKNOWN;
        candidate = UNKNOWN;
        return;
    }
  }
  else if (global()->gameEngine.gameState == constants::PLAYING) {
    switch(e.key.code){
      case sf::Keyboard::W:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            input = constants::INPUT_LEFT_UP;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            input = constants::INPUT_RIGHT_UP;
        }else{
          input = constants::INPUT_UP;
        }
        candidate = PLAYER;
        return;
      case sf::Keyboard::S:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            input = constants::INPUT_LEFT_DOWN;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            input = constants::INPUT_RIGHT_DOWN;
        }else{
          input = constants::INPUT_DOWN;
        }
        candidate = PLAYER;
        return;
      case sf::Keyboard::D:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            input = constants::INPUT_RIGHT_UP;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            input = constants::INPUT_RIGHT_DOWN;
        }else{
          input = constants::INPUT_RIGHT;
        }
        candidate = PLAYER;
        return;
      case sf::Keyboard::A:
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            input = constants::INPUT_LEFT_UP;
        }else if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            input = constants::INPUT_LEFT_DOWN;
        }else{
          input = constants::INPUT_LEFT;
        }
        candidate = PLAYER;
        return;
      case sf::Keyboard::F:
        input = constants::INPUT_ITEM;
        //candidate = ?;
        return;
      case sf::Keyboard::R:
        input =  constants::INPUT_USE;
        //candidate = ?;
        return;
      case sf::Keyboard::E:
        input = constants::INPUT_NEXTITEM;
        //candidate = ?;
        return;
      case sf::Keyboard::Q:
        input = constants::INPUT_PREVITEM;
        //candidate = ?;
        return;
      case sf::Keyboard::P:
        input = constants::INPUT_PAUSE;
        //candidate = ?;
        return;
      default:
        input = constants::INPUT_UNKNOWN;
        candidate = UNKNOWN;
        return;
    }
  }
  else if (global()->gameEngine.gameState == constants::PAUSED) {
      switch(e.key.code){
        case sf::Keyboard::Return:
          input = constants::INPUT_CONFIRM;
          //candidate = ?;
          return;
        default:
          input = constants::INPUT_UNKNOWN;
          candidate = UNKNOWN;
          return;
      }
  }
}
void InputSystem::handleMouseInput(sf::Event &e, constants::Input &input, InputCandidate &candidate){

}
