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
  } else if (type ==  ENEMY_MOVING) {
    this->createMovingEnemy(xy, texture);
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
  sprite->setOrigin(25,25);
  ///////////////////////////////////////////////////////////

  GraphicsComponent *gc = new GraphicsComponent(sprite);
  ControllableComponent *conc = new ControllableComponent();
  MoveableComponent *mc = new MoveableComponent(1200.0,80000.0, 300.0); //accel, decel, max speed
  CollidableComponent *colc = new CollidableComponent(e->getXY(), 50.0, 50.0);



  e->addComponent(gc);
  e->addComponent(conc);
  e->addComponent(mc);
  e->addComponent(colc);


  em->addEntity(e);
  em->setPlayer(e);
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
  sprite->setOrigin(25, 25);
  ///////////////////////////////////////////////////////////

  GraphicsComponent *gc = new GraphicsComponent(sprite);
  CollidableComponent *colc = new CollidableComponent(e->getXY(), 50.0, 50.0);
  BlockVisionComponent *bsc = new BlockVisionComponent(e->getXY(), 50.0, 50.0);

  // VisionComponent *vc = new VisionComponent(e->getXY(), 300, rand()%360, 90);
  // e->addComponent(vc);

  e->addComponent(bsc);
  e->addComponent(gc);
  e->addComponent(colc);
  em->addEntity(e);

}

void EntityCreator::createMovingEnemy(sf::Vector2f xy, sf::Texture *texture) {
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
  sprite->setOrigin(25,25);
  ///////////////////////////////////////////////////////////
  EnemyComponent *ec = new EnemyComponent();

  GraphicsComponent *gc = new GraphicsComponent(sprite);
  //ControllableComponent *conc = new ControllableComponent();
  MoveableComponent *mc = new MoveableComponent(1200.0,80000.0, 100.0); //accel, decel, max speed
  mc->setMaxXPos(e->getXY().x + 200);
  mc->setMinXPos(e->getXY().x - 200);
  mc->setMaxYPos(e->getXY().y);
  mc->setMinYPos(e->getXY().y);
  mc->setAccelerating(true);
  mc->setDirection(180);
  CollidableComponent *colc = new CollidableComponent(e->getXY(), 50.0, 50.0);

    VisionComponent *vc = new VisionComponent(e->getXY(), 300, 270, 90);
  if(xy.y < 400){

    vc->setDirection(90);
    // mc->setDirection(0);
  }
  e->addComponent(vc);
  e->addComponent(ec);
  e->addComponent(gc);
  //e->addComponent(conc);
  e->addComponent(mc);
  e->addComponent(colc);


  em->addEntity(e);

}
