#ifndef _CONFIG_H_
#define _CONFIG_H_

#include "constants.h"
#include "entityManager.h"
#include "graphicsSystem.h"
#include "inputSystem.h"
#include "logicSystem.h"
#include <SFML/Graphics.hpp>

class GraphicsSystem;
//class InputSystem;
//class LogicSystem;
namespace config_internal { //this namespace is not supposed to use outside the file
  class GameEngine {
    public:
      GameEngine(){}

      GameState gameState;
      EntityManager *entityM_P;
      sf::RenderWindow *renderWindow_P;
      //GraphicsSystem *graphicsSystem_P;
      //LogicSystem *logicSystem_P;
      //InputSystem *inputSystem_P;
  };
}


class Config {

    static Config *singleton;

  public:
    Config(){}
    config_internal::GameEngine gameEngine;

    static Config *getSingleton(){return singleton;}
    static void init();
};
static Config *config(){
  return Config::getSingleton();
}

#endif
