#include "graphicsSystem.h"
#include "global.h"
#include <iostream>

GraphicsSystem::GraphicsSystem(sf::RenderWindow* w, EntityManager* m){
  screen = w;
  manager = m;
}


void GraphicsSystem::update(float time){
  if (global()->gameEngine.gameState == constants::PLAYING || global()->gameEngine.gameState == constants::PAUSED ||
  global()->gameEngine.nonPlaying->getState() == NonPlaying::TERMINALMENU) {
    sf::View view;
    view.setCenter(manager->getPlayer()->getXY());
    view.setSize(sf::Vector2f(800, 600));

    screen->setView(view);

    //This is definitely the wrong place to create the background, but trying to create an entity crashed it....
    sf::Texture *background = new sf::Texture();
    background->loadFromFile("resources/graphics/sprite/floor.png");
    background->setRepeated(true);
    sf::Sprite *background_sprite = new sf::Sprite;
    background_sprite->setTexture(*background);
    background_sprite->setTextureRect(sf::IntRect(0,0,10000,10000));
    background_sprite->setOrigin(25.0f, 25.0f);
    background_sprite->setPosition(-5000.0f, -5000.0f);
    draw(background_sprite);

    //iterate through entityManager and update
    std::list<Entity*>* eList = manager->getEntityList();
    std::list<Entity*>::iterator iterator;
    for (iterator = eList->begin(); iterator != eList->end(); ++iterator) {
      if((*iterator)->hasComponent(constants::GRAPHICS)){
        if((*iterator)->hasComponent(constants::TRAPC)) {
          TrapComponent *trc = (TrapComponent*)(*iterator)->getComponent(constants::TRAPC);
          //only draw if trap is visible
          if(trc->getVisibility()) {
            //it is a graphics component, so we can cast it
            GraphicsComponent *gp = (GraphicsComponent*)(*iterator)->getComponent(constants::GRAPHICS);
            gp->getSprite()->setPosition((*iterator)->getXY());
            //gp->getSprite()->setPosition(sf::Vector2f(iterator->getXY().x - gp->getSprite()->getLocalBounds().width/2, iterator->getXY().y - gp->getSprite()->getLocalBounds().height/2)) ;
            draw((gp->getSprite()));
          }
        } else {
          //it is a graphics component, so we can cast it
          GraphicsComponent *gp = (GraphicsComponent*)(*iterator)->getComponent(constants::GRAPHICS);
          gp->getSprite()->setPosition((*iterator)->getXY());
          //gp->getSprite()->setPosition(sf::Vector2f(iterator->getXY().x - gp->getSprite()->getLocalBounds().width/2, iterator->getXY().y - gp->getSprite()->getLocalBounds().height/2)) ;
          draw((gp->getSprite()));
        }
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
        draw(&va);
      }
      if ((*iterator)->hasComponent(constants::INVENTORY)) {
        InventoryComponent *ip = (InventoryComponent *) (*iterator)->getComponent(constants::INVENTORY);
        ip->draw(*screen, view);
      }
    }
    if (global()->gameEngine.gameState == constants::PAUSED) {
      sf::Texture *pausedTex = new sf::Texture();
      pausedTex->loadFromFile("resources/graphics/image/paused.png");
      sf::Sprite *pausedSprite = new sf::Sprite();
      pausedSprite->setTexture(*pausedTex);
      draw(pausedSprite);
    }
  }
  if (global()->gameEngine.gameState == constants::NONPLAYING ) {
    global()->gameEngine.nonPlaying->draw(*screen);
  }
}

void GraphicsSystem::draw(sf::Drawable *drawable){
  screen->draw(*drawable);
}
void GraphicsSystem::draw(void (*callback)(sf::RenderWindow* w)) {
  callback(this->screen);
}
