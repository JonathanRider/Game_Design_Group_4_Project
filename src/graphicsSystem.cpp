#include "graphicsSystem.h"
#include "global.h"
#include <iostream>

GraphicsSystem::GraphicsSystem(sf::RenderWindow* w, EntityManager* m){
  screen = w;
  manager = m;
}


void GraphicsSystem::update(float time){

  if (global()->gameEngine.gameState == constants::MENU) {

    // sf::Texture *menuTex = new sf::Texture();
    // menuTex->loadFromFile("resources/MainMenu.png");
    // sf::Sprite *menuSprite = new sf::Sprite();
    // menuSprite->setTexture(*menuTex);
    // screen->draw(*menuSprite);

  } else if (global()->gameEngine.gameState == constants::PLAYING || global()->gameEngine.gameState == constants::PAUSED) {

    //iterate through entityManager and update
    std::list<Entity*>* eList = manager->getEntityList();
    std::list<Entity*>::iterator iterator;
    for (iterator = eList->begin(); iterator != eList->end(); ++iterator) {
      if((*iterator)->hasComponent(constants::GRAPHICS)){
        //it is a graphics component, so we can cast it
        GraphicsComponent *gp = (GraphicsComponent*)(*iterator)->getComponent(constants::GRAPHICS);
        gp->getSprite()->setPosition((*iterator)->getXY());
        //gp->getSprite()->setPosition(sf::Vector2f(iterator->getXY().x - gp->getSprite()->getLocalBounds().width/2, iterator->getXY().y - gp->getSprite()->getLocalBounds().height/2)) ;
        screen->draw(*(gp->getSprite()));
      }
      if((*iterator)->hasComponent(constants::VISION)){

        VisionComponent *vp = (VisionComponent*)(*iterator)->getComponent(constants::VISION);
        sf::VertexArray va= *(vp->getTriangles());

        sf::Color vp_color;
        if (vp->getAlert())
          vp_color =sf::Color(255,0,0,128);
        else
          vp_color = sf::Color(0,255,0,128);

        for(int i = 0; i < va.getVertexCount(); i++){
          va[i].color = vp_color;
        }
         screen->draw(va);
      }
    }
    if (global()->gameEngine.gameState == constants::PAUSED) {
      sf::Texture *pausedTex = new sf::Texture();
      pausedTex->loadFromFile("resources/paused.png");
      sf::Sprite *pausedSprite = new sf::Sprite();
      pausedSprite->setTexture(*pausedTex);
      screen->draw(*pausedSprite);
    }
  }
}
