#include "entityCreator.h"

#include <iostream>

EntityCreator::~EntityCreator() {
  // delete em;
  //
  // delete e;
  // delete curTexture;
  // delete mc;
  // delete gc;
  // delete colc;
  // delete conc;
}

void EntityCreator::create(EntityType type, sf::Vector2f xy, sf::Texture *texture) {
  if (type == PLAYER) {
    this->createPlayer(xy, texture);
  } else if (type == WALL) {
    this->createWall(xy, texture);
  }
  //not valid entityType
}

void EntityCreator::createPlayer(sf::Vector2f xy, sf::Texture *texture) {
  Entity *e = new Entity(em->getNewID());
  e->setXY(xy);

  //////////////////this should probably be moved somewhere else
  //load texture
  // if(playerTexture == NULL){
  //   playerTexture = new sf::Texture();
  //   playerTexture->loadFromFile("resources/test.png");
  // }
  //create sprite
  sf::Sprite *sprite = new sf::Sprite();
  sprite->setTexture(*texture);
  ///////////////////////////////////////////////////////////

  GraphicsComponent *gc = new GraphicsComponent(sprite);
  ControllableComponent *conc = new ControllableComponent();
  MoveableComponent *mc = new MoveableComponent(1200.0,80000.0, 300.0); //accel, decel, max speed
  CollidableComponent *colc = new CollidableComponent(e->getXY(), 50.0, 50.0);

  e->addComponent(gc);
  e->addComponent(conc);
  e->addComponent(mc);
  e->addComponent(colc);

  em->addEntity(*e);
}

void EntityCreator::createWall(sf::Vector2f xy, sf::Texture *texture) {
  Entity *e = new Entity(em->getNewID());
  e->setXY(xy);
  //////////////////this should probably be moved somewhere else
  //load texture
  // if(texture == NULL){
  //   texture = new sf::Texture();
  //   texture->loadFromFile("resources/test.png");
  //   std::cout << "NULL";
  // }
  //create sprite
  sf::Sprite *sprite = new sf::Sprite();
  sprite->setTexture(*texture);
  ///////////////////////////////////////////////////////////

  //GraphicsComponent *gc = new GraphicsComponent(sprite);
  CollidableComponent *colc = new CollidableComponent(e->getXY(), 50.0, 50.0);

  //e->addComponent(gc);
  e->addComponent(colc);
}
