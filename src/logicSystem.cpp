#include "logicSystem.h"
#include "allComponents.h"
#include <iostream>


LogicSystem::LogicSystem(EntityManager *m, GameState s)
  :manager(m), state(s){}

void LogicSystem::update(float time){


  //for each component type that we want to do stuff with

  /*
  std::list<Entity>* eList = manager->getEntityList();
  std::list<Entity>::iterator iterator;
  for (iterator = eList->begin(); iterator != eList->end(); ++iterator) {
    if(iterator->hasComponent(GRAPHICS)){
      GraphicsComponent *gp = (GraphicsComponent*)iterator->getComponent(GRAPHICS);
      gp->getSprite()->setPosition(iterator->getXY());
      screen->draw(*(gp->getSprite()));
    }
  }
  */



}
