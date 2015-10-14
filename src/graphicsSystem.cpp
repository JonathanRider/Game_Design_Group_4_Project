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
      //gp->getSprite()->setPosition(sf::Vector2f(iterator->getXY().x - gp->getSprite()->getLocalBounds().width/2, iterator->getXY().y - gp->getSprite()->getLocalBounds().height/2)) ;
      screen->draw(*(gp->getSprite()));
    }
    if(iterator->hasComponent(VISION)){

      VisionComponent *vp = (VisionComponent*)iterator->getComponent(VISION);
      sf::VertexArray va= *(vp->getTriangles());
      for(int i = 0; i < va.getVertexCount(); i++){
        va[i].color = sf::Color(255,0,0,128);
      }



       screen->draw(va);
    }




  }
}
