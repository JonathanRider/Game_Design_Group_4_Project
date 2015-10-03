#include "graphicsSystem.h"
#include <iostream>

GraphicsSystem::GraphicsSystem(sf::RenderWindow* w, EntityManager* m, GameState s){
  screen = w;
  manager = m;
  state = s;
}


void GraphicsSystem::update(float time){
  //iterate through entityManager and update
  std::list<Entity>* eList = manager->getEntityList();
  std::list<Entity>::iterator iterator;
  for (iterator = eList->begin(); iterator != eList->end(); ++iterator) {
    if(iterator->hasComponent(GRAPHICS)){
      //it is a graphics component, so we can cast it
      GraphicsComponent *gp = (GraphicsComponent*)iterator->getComponent(GRAPHICS);
      gp->getSprite()->setPosition(iterator->getXY());
      screen->draw(*(gp->getSprite()));
    }
  }
}
