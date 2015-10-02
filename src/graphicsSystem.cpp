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
      graphicsComponent *gp = (graphicsComponent*)iterator->getComponent(1);
      gp->draw(screen, iterator->getXY());
    }

  }


}
