#include "graphicsSystem.h"
#include <iostream>

graphicsSystem::graphicsSystem(sf::RenderWindow* w, entityManager* m, int vType){
  screen = w;
  manager = m;
  viewType = vType;
}


void graphicsSystem::update(float time){
  //iterate through entityManager and update
  std::list<entity>* eList = manager->getEntityList();
  std::list<entity>::iterator iterator;
  for (iterator = eList->begin(); iterator != eList->end(); ++iterator) {
    if(iterator->hasComponent(1)){
      //it is a graphics component, so we can cast it
      graphicsComponent *gp = (graphicsComponent*)iterator->getComponent(1);
      gp->getSprite()->setPosition(iterator->getXY());
      screen->draw(*(gp->getSprite()));
    }
  }
}
