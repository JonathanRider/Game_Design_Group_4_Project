#include "inputSystem.h"
#include "global.h"
#include <cmath>
#include <iostream>

#define MOUSE_LEFT_PRESSED 1<<0
#define KEY_A_PRESSED 1<<1
#define KEY_W_PRESSED 1<<2
#define KEY_S_PRESSED 1<<3
#define KEY_D_PRESSED 1<<4
#define KEY_F_PRESSED 1<<5
#define KEY_E_PRESSED 1<<6
#define KEY_Q_PRESSED 1<<7
#define KEY_R_PRESSED 1<<8
#define KEY_P_PRESSED 1<<9
#define KEY_ENTER_PRESSED 1<<10
#define KEY_UP_PRESSED 1<<11
#define KEY_DOWN_PRESSED 1<<12

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

  unsigned long input_container = 0;
  sf::Vector2f mouse_position;

  input_container |= getKeyInput();
  input_container |= getMouseInput(mouse_position);

  //feed the input to every possible parties...
  manager->getPlayer()->receiveInput(interprertForPlayer(input_container));
  global()->gameEngine.logicSystem->receveInput(interpretForLogicSystem(input_container), (void *) &mouse_position);
}

unsigned long InputSystem::getKeyInput() {
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
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::E)){
    ret_val |= KEY_E_PRESSED;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::F)){
    ret_val |= KEY_F_PRESSED;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)){
    ret_val |= KEY_R_PRESSED;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)){
    ret_val |= KEY_Q_PRESSED;
  }
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
unsigned long InputSystem::getMouseInput(sf::Vector2f &position) {
  unsigned long ret_val = 0;
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
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
    switch(e.key.code) {
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
