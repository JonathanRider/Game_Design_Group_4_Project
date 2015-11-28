#include "inputSystem.h"
#include "global.h"
#include <cmath>
#include <iostream>

#define MOUSE_LEFT_PRESSED 1<<0
#define KEY_A_PRESSED 1<<1
#define KEY_W_PRESSED 1<<2
#define KEY_S_PRESSED 1<<3
#define KEY_D_PRESSED 1<<4
#define KEY_F_PRESSED 1<<5 //constants::INPUT_ITEM
#define KEY_E_PRESSED 1<<6 //constants::INPUT_NEXTITEM;
#define KEY_Q_PRESSED 1<<7 //constants::INPUT_PREVITEM;
#define KEY_R_PRESSED 1<<8 //constants::INPUT_USE
#define KEY_P_PRESSED 1<<9 //constants::INPUT_PAUSE;
#define KEY_ENTER_PRESSED 1<<10
#define KEY_UP_PRESSED 1<<11
#define KEY_DOWN_PRESSED 1<<12

InputSystem::InputSystem(EntityManager *m, sf::RenderWindow *w, LevelCreator *lc)
  :manager(m), screen(w), lCreator(lc){  }

void InputSystem::update(float time){
  sf::Event event;
  //get the event
  screen->pollEvent(event);


  if(event.type == sf::Event::Closed ) {
    //we should shut down the game now..
    global()->gameEngine.gameState = constants::CLOSING;
    return;
  }

  unsigned long input_container = 0;
  sf::Vector2f mouse_position;

  //feed the input to every possible parties...
  if (global()->gameEngine.gameState == constants::PLAYING){
    input_container |= getKeyInputEvent(event);
    input_container |= getKeyInputPolling();
    input_container |= getMouseInputEvent(event, mouse_position);
    manager->getPlayer()->receiveInput(interprertForPlayer(input_container));
    manager->getInventory()->receiveInput(interprertForInventory(input_container));
    global()->gameEngine.logicSystem->receiveInput(interpretForLogicSystem(input_container), (void *) &mouse_position);
  }

  else {
    input_container |= getKeyInputEvent(event);
    handleMenu(interpretForMenu(input_container));
  }

}

unsigned long InputSystem::getKeyInputPolling() {
  unsigned long ret_val = 0;
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)){
    ret_val |= KEY_W_PRESSED;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)){
    ret_val |= KEY_A_PRESSED;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
    ret_val |= KEY_S_PRESSED;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)){
    ret_val |= KEY_D_PRESSED;
  }
//  if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
//    ret_val |= KEY_E_PRESSED;
//  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
    ret_val |= KEY_F_PRESSED;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
    ret_val |= KEY_R_PRESSED;
  }
//  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
//    ret_val |= KEY_Q_PRESSED;
//  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
    ret_val |= KEY_P_PRESSED;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
    ret_val |= KEY_ENTER_PRESSED;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
    ret_val |= KEY_UP_PRESSED;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
    ret_val |= KEY_DOWN_PRESSED;
  }
  return ret_val;
}
unsigned long InputSystem::getMouseInputPolling(sf::Vector2f &position) {
  unsigned long ret_val = 0;
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
    ret_val |= MOUSE_LEFT_PRESSED;
    position.x = sf::Mouse::getPosition(*screen).x;
    position.y = sf::Mouse::getPosition(*screen).y;
  }
  return ret_val;
}
unsigned long InputSystem::getKeyInputEvent(sf::Event &event) {
  unsigned long ret_val = 0;
  if ( event.type != sf::Event::KeyPressed ) {
    return ret_val;
  }
  switch(event.key.code){
    case sf::Keyboard::E:
      ret_val |= KEY_E_PRESSED;
      break;
    case sf::Keyboard::Q:
      ret_val |= KEY_Q_PRESSED;
      break;
    case sf::Keyboard::Return:
      ret_val |= KEY_ENTER_PRESSED;
      break;
    case sf::Keyboard::Up:
      ret_val |= KEY_UP_PRESSED;
      break;
    case sf::Keyboard::Down:
      ret_val |= KEY_DOWN_PRESSED;
    default:
      break;
  }
  return ret_val;
}
unsigned long InputSystem::getMouseInputEvent(sf::Event &event, sf::Vector2f &position){
  unsigned long ret_val = 0;
  if ( event.type != sf::Event::MouseButtonPressed ) {
    return ret_val;
  }
  if (event.mouseButton.button == sf::Mouse::Left){
      ret_val |= MOUSE_LEFT_PRESSED;
      position.x = sf::Mouse::getPosition(*screen).x;
      position.y = sf::Mouse::getPosition(*screen).y;
  }
  return ret_val;
}


constants::Input InputSystem::interprertForPlayer(unsigned long input){
  unsigned long key_pressed = input & (KEY_A_PRESSED | KEY_W_PRESSED | KEY_S_PRESSED | KEY_D_PRESSED);
  switch (key_pressed) {
    case KEY_A_PRESSED | KEY_W_PRESSED:
      return constants::INPUT_LEFT_UP;
    case KEY_D_PRESSED | KEY_W_PRESSED:
      return constants::INPUT_RIGHT_UP;
    case KEY_A_PRESSED | KEY_S_PRESSED:
      return constants::INPUT_LEFT_DOWN;
    case KEY_D_PRESSED | KEY_S_PRESSED:
      return constants::INPUT_RIGHT_DOWN;
    case KEY_W_PRESSED:
      return constants::INPUT_UP;
    case KEY_S_PRESSED:
      return constants::INPUT_DOWN;
    case KEY_A_PRESSED:
      return constants::INPUT_LEFT;
    case KEY_D_PRESSED:
      return constants::INPUT_RIGHT;
    default:
      return constants::INPUT_UNKNOWN;
  }
}

constants::Input InputSystem::interpretForLogicSystem(unsigned long input) {
  unsigned long key_pressed = input & ( MOUSE_LEFT_PRESSED );
  switch (key_pressed) {
    case MOUSE_LEFT_PRESSED:
      return constants::INPUT_SHOOT;
    default:
      return constants::INPUT_UNKNOWN;
  }
}

constants::Input InputSystem::interpretForMenu(unsigned long input) {
  if ( input & KEY_UP_PRESSED ) {
    return constants::INPUT_UP;
  }
  else if (input & KEY_DOWN_PRESSED) {
    return constants::INPUT_DOWN;
  }
  else if (input & KEY_ENTER_PRESSED) {
    return constants::INPUT_CONFIRM;
  }
  return constants::INPUT_UNKNOWN;
}

constants::Input InputSystem::interprertForInventory(unsigned long input){
  unsigned long key_pressed = input & (KEY_Q_PRESSED | KEY_E_PRESSED);
  switch (key_pressed) {
    case KEY_Q_PRESSED:
      return constants::INPUT_PREVITEM;
    case KEY_E_PRESSED:
      return constants::INPUT_NEXTITEM;
    default:
      return constants::INPUT_UNKNOWN;
  }
}

void InputSystem::handleMenu(constants::Input input){
  switch(global()->gameEngine.gameState) {
    case constants::MENU:
            switch (input) {
              case constants::INPUT_UP:
                std::cout << "up" << std::endl;
                if (global()->gameEngine.mainMenuState <= 0) {
                  global()->gameEngine.mainMenuState = 1; //max number of options
                } else {
                  global()->gameEngine.mainMenuState -= 1;
                }
                break;
              case constants::INPUT_DOWN:
              std::cout << "down" << std::endl;
                if (global()->gameEngine.mainMenuState >= 1) {//max number of options
                  global()->gameEngine.mainMenuState = 0;
                } else {
                  global()->gameEngine.mainMenuState += 1;
                }
                break;
              case constants::INPUT_CONFIRM:
              std::cout << "confirm" << std::endl;
                switch(global()->gameEngine.mainMenuState) {
                  case 0: //first menu option
                    std::cout << "levelMenu" << std::endl;
                    global()->gameEngine.gameState = constants::LEVELMENU;
                    break;
                  case 1:  //second menu option
                    global()->gameEngine.gameState = constants::OPTIONSMENU;
                    std::cout << "options" << std::endl;
                    break;
                  default:
                    break;
                }
                break;
              default:
                break;
            }
          return;
        case constants::LEVELMENU:
          switch (input) {
            case constants::INPUT_UP:
              if (global()->gameEngine.levelMenuState <= 0) {
                global()->gameEngine.levelMenuState = 2; //max number of options
              } else {
                global()->gameEngine.levelMenuState -= 1;
              }
              break;
            case constants::INPUT_DOWN:
              if (global()->gameEngine.levelMenuState >= 2) {//max number of options
                global()->gameEngine.levelMenuState = 0;
              } else {
                global()->gameEngine.levelMenuState += 1;
              }
              break;
            case constants::INPUT_CONFIRM:
              {
              std::cout << "confirm" << std::endl;
              std::string fileName = ""; //change based on what level is selected
              switch(global()->gameEngine.levelMenuState) {
                case 0: //level 0
                  fileName = "resources/levels/level_01.xml";
                  break;
                case 1:  //level 1
                  fileName = "resources/levels/level_02.xml";
                  break;
                case 2:  //level 2
                  fileName = "resources/levels/level_03.xml";
                  break;
                default:
                  fileName = "resources/levels/level_01.xml";
                  break;
              }
              manager->clearAll();
              lCreator->loadLevelFile(fileName);
              lCreator->createLevel();

              global()->gameEngine.gameState = constants::PLAYING;
            } //end of confirm case
          default:
            break;
          }
          return;
        case constants::OPTIONSMENU:
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
          return;
    case constants::GAMEOVER:
      switch (input) {
        case constants::INPUT_CONFIRM:
          global()->gameEngine.gameState = constants::LEVELMENU;
          break;
        default:
          break;
      }
      return;
    case constants::WIN:
      switch (input) {
        case constants::INPUT_CONFIRM:
          global()->gameEngine.gameState = constants::LEVELMENU;
          break;
        default:
          break;
      }
      return;
    default:
      return;
  }
}
