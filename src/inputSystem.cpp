#include "inputSystem.h"
#include "global.h"
#include <cmath>
#include <iostream>


InputSystem::InputSystem(EntityManager *m, sf::RenderWindow *w, LevelCreator *lc)
  :manager(m), screen(w), lCreator(lc){}

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
    case MAINMENU:
        switch (input) {
          case constants::INPUT_UP:
            std::cout << "up";
            if (global()->gameEngine.mainMenuState <= 0) {
              global()->gameEngine.mainMenuState = 1; //max number of options
            } else {
              global()->gameEngine.mainMenuState -= 1;
            }
            break;
          case constants::INPUT_DOWN:
          std::cout << "down";
            if (global()->gameEngine.mainMenuState >= 1) {//max number of options
              global()->gameEngine.mainMenuState = 0;
            } else {
              global()->gameEngine.mainMenuState += 1;
            }
            break;
          case constants::INPUT_CONFIRM:
          std::cout << "confirm";
            switch(global()->gameEngine.levelMenuState) {
              case 0: //first menu option
                std::cout << "levelMenu";
                global()->gameEngine.gameState = constants::LEVELMENU;
                break;
              case 1:  //second menu option
                global()->gameEngine.gameState = constants::OPTIONSMENU;
                break;
              default:
                break;
            }
            break;
          default:
            break;
        }
      break;
    case LEVELMENU:
      switch (input) {
        case constants::INPUT_UP:
          if (global()->gameEngine.levelMenuState <= 0) {
            global()->gameEngine.levelMenuState = 1; //max number of options
          } else {
            global()->gameEngine.levelMenuState -= 1;
          }
          break;
        case constants::INPUT_DOWN:
          if (global()->gameEngine.levelMenuState >= 1) {//max number of options
            global()->gameEngine.levelMenuState = 0;
          } else {
            global()->gameEngine.levelMenuState += 1;
          }
          break;
        case constants::INPUT_CONFIRM:
          {
          std::cout << "confirm";
          std::string fileName = ""; //change based on what level is selected
          switch(global()->gameEngine.levelMenuState) {
            case 0: //level 0
              fileName = "resources/levels/level_01.xml";
              break;
            case 1:  //level 1
              fileName = "resources/levels/level_01.xml";
              break;
            default:
              fileName = "resources/levels/level_01.xml";
              break;
          }
          lCreator->loadLevelFile(fileName);
          lCreator->createLevel();
          global()->gameEngine.gameState = constants::PLAYING;
        } //end of confirm case
      default:
        break;
      }
    case OPTIONSMENU:
      switch (input) {
        case constants::INPUT_UP:
          if (global()->gameEngine.optionsMenuState <= 0) {
            global()->gameEngine.optionsMenuState = 1; //max number of options
          } else {
            global()->gameEngine.optionsMenuState -= 1;
          }
          break;
        case constants::INPUT_DOWN:
          if (global()->gameEngine.optionsMenuState >= 1) {//max number of options
            global()->gameEngine.optionsMenuState = 0;
          } else {
            global()->gameEngine.optionsMenuState += 1;
          }
          break;
        case constants::INPUT_CONFIRM:
          //do something
          break;
        default:
          break;
      }
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
        input = constants::INPUT_UP;
        candidate = MAINMENU;
        return;
      case sf::Keyboard::Down:
        input = constants::INPUT_DOWN;
        candidate = MAINMENU;
        return;
      case sf::Keyboard::Return:
        input = constants::INPUT_CONFIRM;
        candidate = MAINMENU;
        return;
      default:
        input = constants::INPUT_UNKNOWN;
        candidate = UNKNOWN;
        return;
    }
  }
  else if (global()->gameEngine.gameState == constants::LEVELMENU) {
    switch(e.key.code){
      case sf::Keyboard::Up:
        input = constants::INPUT_UP;
        candidate = LEVELMENU;
        return;
      case sf::Keyboard::Down:
        input = constants::INPUT_DOWN;
        candidate = LEVELMENU;
        return;
      case sf::Keyboard::Return:
        input = constants::INPUT_CONFIRM;
        candidate = LEVELMENU;
        return;
      default:
        input = constants::INPUT_UNKNOWN;
        candidate = LEVELMENU;
        return;
    }
  }
  else if (global()->gameEngine.gameState == constants::OPTIONSMENU) {
    switch(e.key.code){
      case sf::Keyboard::Up:
        input = constants::INPUT_UP;
        candidate = OPTIONSMENU;
        return;
      case sf::Keyboard::Down:
        input = constants::INPUT_DOWN;
        candidate = OPTIONSMENU;
        return;
      case sf::Keyboard::Return:
        input = constants::INPUT_CONFIRM;
        candidate = OPTIONSMENU;
        return;
      default:
        input = constants::INPUT_UNKNOWN;
        candidate = OPTIONSMENU;
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
