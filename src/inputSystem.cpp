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
#define KEY_LEFT_PRESSED 1<<13
#define KEY_RIGHT_PRESSED 1<<14
#define KEY_ESC_PRESSED 1<<15 //constants::INPUT_ESC

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
    input_container |= getMouseInputPolling(mouse_position);
    input_container |= getMouseInputEvent(event, mouse_position);
    manager->getPlayer()->receiveInput(interprertForPlayer(input_container),(void *) &mouse_position );
    manager->getInventory()->receiveInput(interprertForInventory(input_container));
    global()->gameEngine.logicSystem->receiveInput(interpretForLogicSystem(input_container), (void *) &mouse_position);
  } else if (global()->gameEngine.gameState == constants::PAUSED){
      input_container |= getKeyInputEvent(event);
      input_container |= getKeyInputPolling();
      input_container |= getMouseInputEvent(event, mouse_position);
      global()->gameEngine.logicSystem->receiveInput(interpretForLogicSystem(input_container), (void *) &mouse_position);
    }

  else {
    input_container |= getKeyInputEvent(event);
    global()->gameEngine.nonPlaying->receiveInput(interpretForMenu(input_container), NULL);
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
//  if (sf::Keyboard::isKeyPressed(sf::Keyboard::P)){
//    ret_val |= KEY_P_PRESSED;
//  }
//  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)){
//    ret_val |= KEY_ENTER_PRESSED;
//  }
//  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)){
//    ret_val |= KEY_UP_PRESSED;
//  }
//  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)){
//    ret_val |= KEY_DOWN_PRESSED;
//  }
  return ret_val;
}
unsigned long InputSystem::getMouseInputPolling(sf::Vector2f &position) {
  unsigned long ret_val = 0;
//  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
//    ret_val |= MOUSE_LEFT_PRESSED;
//  }
  //sf::Vector2i p;
  //p = sf::Mouse::getPosition(*screen);
  //position = screen->mapPixelToCoords(p);
  position.x = sf::Mouse::getPosition(*screen).x;
  position.y = sf::Mouse::getPosition(*screen).y;
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
    case sf::Keyboard::W:
      ret_val |= KEY_W_PRESSED;
      break;
    case sf::Keyboard::S:
      ret_val |= KEY_S_PRESSED;
      break;
    case sf::Keyboard::A:
      ret_val |= KEY_A_PRESSED;
      break;
    case sf::Keyboard::D:
      ret_val |= KEY_D_PRESSED;
      break;
    case sf::Keyboard::Return:
      ret_val |= KEY_ENTER_PRESSED;
      break;
    case sf::Keyboard::Up:
      ret_val |= KEY_UP_PRESSED;
      break;
    case sf::Keyboard::Down:
      ret_val |= KEY_DOWN_PRESSED;
      break;
    case sf::Keyboard::Left:
      ret_val |= KEY_LEFT_PRESSED;
      break;
    case sf::Keyboard::Right:
      ret_val |= KEY_RIGHT_PRESSED;
      break;
    case sf::Keyboard::Escape:
      ret_val |= KEY_ESC_PRESSED;
      break;
    case sf::Keyboard::P:
      ret_val |= KEY_P_PRESSED;
      break;
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
  unsigned long key_pressed = input & ( MOUSE_LEFT_PRESSED | KEY_P_PRESSED);
  switch (key_pressed) {
    case MOUSE_LEFT_PRESSED:
      return constants::INPUT_SHOOT;
    case KEY_P_PRESSED:
      std::cout <<"interpret pause" << std::endl;
      return constants::INPUT_PAUSE;
    default:
      return constants::INPUT_UNKNOWN;
  }
}

constants::Input InputSystem::interpretForMenu(unsigned long input) {
  if ( input & KEY_UP_PRESSED  | input & KEY_W_PRESSED) {
    return constants::INPUT_UP;
  }
  else if (input & KEY_DOWN_PRESSED | input & KEY_S_PRESSED) {
    return constants::INPUT_DOWN;
  }
  else if (input & KEY_LEFT_PRESSED | input & KEY_A_PRESSED) {
    return constants::INPUT_LEFT;
  }
  else if (input & KEY_RIGHT_PRESSED | input & KEY_D_PRESSED) {
    return constants::INPUT_RIGHT;
  }
  else if (input & KEY_ENTER_PRESSED) {
    return constants::INPUT_CONFIRM;
  }
  else if (input & KEY_ESC_PRESSED) {
    return constants::INPUT_ESC;
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
