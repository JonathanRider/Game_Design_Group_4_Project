#ifndef _GLOBAL_H_
#define _GLOBAL_H_

#include "config.h"
#include "logicSystem.h"
#include "entityCreator.h"
#include "audioSystem.h"
#include "resourceManager.h"
#include "nonPlaying.h"
#include "entityManager.h"
#include "levelCreator.h"

class NonPlaying;
namespace global_internal{ //this namespace is not supposed to use outside the file
  class GameEngine { //used to store some information for run-time
    public:
      GameEngine(){}
      LogicSystem *logicSystem;
      EntityCreator *entityCreator;
      AudioSystem *audioSystem;
      ResourceManager *resourceManager;
      NonPlaying *nonPlaying;
      EntityManager *entityManager;
      LevelCreator *levelCreator;
      constants::GameState gameState;
  };
}


class Global {

    static Global *singleton;

  public:
    Config config;
    global_internal::GameEngine gameEngine;
    static Global *getSingleton(){return singleton;}
    static void init(){singleton = new Global();}
    static void clean(){
      delete singleton;
      singleton = NULL;
    }
};

static Global *global(){
  return Global::getSingleton();
}

#endif
