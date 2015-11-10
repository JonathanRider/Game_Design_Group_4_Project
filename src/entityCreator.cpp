#include "entityCreator.h"
#include <cmath>

#include <iostream>

EntityCreator::EntityCreator(EntityManager *em):em(em){
  for(int i=0; i < NUM_OF_TEXTURES; i++) {
    texture_table.push_back(new sf::Texture());
  }
  texture_table[WALL]->loadFromFile("resources/wall.png");
  texture_table[PLAYER]->loadFromFile("resources/roy.png");
  texture_table[ENEMY]->loadFromFile("resources/soldier.png");
  texture_table[BULLET]->loadFromFile("resources/bullet.png");
}

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

void EntityCreator::create(constants::EntityType type, sf::Vector2f xy) {
  if (type == constants::PLAYER) {
    this->createPlayer(xy);
  } else if (type == constants::WALL) {
    // this->createWall(xy, texture);
  } else if (type ==  constants::ENEMY_MOVING) {
    this->createMovingEnemy(xy);
  } else if (type == constants::FINISH) {
    this->createFinish(xy);
  }


  //not valid entityType
}

void EntityCreator::createPlayer(sf::Vector2f xy) {
  Entity *e = new Entity(em->getNewID());
  e->setXY(xy);
  e->setBoundingBox(new sf::FloatRect(xy.x-25, xy.y-25, 50, 50));


  //////////////////this should probably be moved somewhere else
  //load texture
  // if(playerTexture == NULL){
  //   playerTexture = new sf::Texture();
  //   playerTexture->loadFromFile("resources/test.png");
  // }
  //create sprite
  sf::Sprite *sprite = new sf::Sprite();
  sprite->setTexture(* texture_table[PLAYER]);
  sprite->setOrigin(25,25);
  sprite->setRotation(90.0f);
  ///////////////////////////////////////////////////////////

  GraphicsComponent *gc = new GraphicsComponent(sprite);
  MoveableComponent *mc = new MoveableComponent(10000.0,80000.0, 300.0); //accel, decel, max speed
  CollidableComponent *colc = new CollidableComponent(e->getXY());

  // VisionComponent *vc = new VisionComponent(e->getXY(), 300, 270, 90);
  // e->addComponent(vc);

  e->addComponent(gc);
  e->addComponent(mc);
  e->addComponent(colc);


  em->addEntity(e);
  em->setPlayer(e);
}

void EntityCreator::createWall(sf::Vector2f xy, float width, float height) {
  Entity *e = new Entity(em->getNewID());
  xy.x += width/2;
  xy.y += height/2;
  e->setXY(xy);
  e->setBoundingBox(new sf::FloatRect(xy.x-width/2, xy.y-height/2, width, height));

  //create sprite
  sf::Sprite *sprite = new sf::Sprite();
  texture_table[WALL]->setRepeated(true);
  sprite->setTexture(* texture_table[WALL]);
  sprite->setOrigin(width/2, height/2);
  // sprite->getTexture()->setRepeated(true);
  sf::IntRect ir;

  ir.width = (int)width;
  ir.height = (int)height;
  sprite->setTextureRect(ir);
  ///////////////////////////////////////////////////////////

  GraphicsComponent *gc = new GraphicsComponent(sprite);
  Component *bmc = new Component(constants::BMOVEMENT);
  BlockVisionComponent *bsc = new BlockVisionComponent(e->getXY(), height, width);

  // VisionComponent *vc = new VisionComponent(e->getXY(), 300, rand()%360, 90);
  // e->addComponent(vc);

  e->addComponent(bsc);
  e->addComponent(gc);
  e->addComponent(bmc);
  em->addEntity(e);

}

void EntityCreator::createMovingEnemy(sf::Vector2f xy) {
  Entity *e = new Entity(em->getNewID());
  e->setXY(xy);
  e->setBoundingBox(new sf::FloatRect(xy.x-25, xy.y-25, 50, 50));
  //create sprite
  sf::Sprite *sprite = new sf::Sprite();
  sprite->setTexture(*texture_table[ENEMY]);
  sprite->setOrigin(25,25);
  ///////////////////////////////////////////////////////////
  Component *ec = new Component(constants::ENEMY);
  e->addComponent(ec);

  GraphicsComponent *gc = new GraphicsComponent(sprite);
  e->addComponent(gc);

  MoveableComponent *mc = new MoveableComponent(1200.0,80000.0, 100.0); //accel, decel, max speed
  mc->setMaxXPos(e->getXY().x + 200);
  mc->setMinXPos(e->getXY().x - 200);
  mc->setMaxYPos(e->getXY().y);
  mc->setMinYPos(e->getXY().y);
  mc->setAccelerating(true);
  mc->setDirection(180);
  e->addComponent(mc);

  CollidableComponent *colc = new CollidableComponent(e->getXY());
  e->addComponent(colc);

    VisionComponent *vc = new VisionComponent(e->getXY(), 300, 270, 90);
  if(xy.y < 400){

    vc->setDirection(90);
    // mc->setDirection(0);
  }
  e->addComponent(vc);

  Component *kc = new Component(constants::KILLABLE);
  e->addComponent(kc);
  //e->addComponent(conc);



  em->addEntity(e);

}

void EntityCreator::createGrenade(sf::Vector2f xy, float direction, float velocity, float drag){
  Entity *e = new Entity(em->getNewID());
  e->setXY(xy);
  e->setBoundingBox(new sf::FloatRect(xy.x-5, xy.y-5, 10, 10));
  // e->setXY(sf::Vector2f(xy.x+50*cos(direction*PI/180), xy.y+50*sin(direction*PI/180)));
  sf::Sprite *sprite = new sf::Sprite();
  sprite->setTexture(*texture_table[BULLET]);
  sprite->setOrigin(5,5);


  GraphicsComponent *gc = new GraphicsComponent(sprite);
  e->addComponent(gc);
  MoveableComponent *mc = new MoveableComponent(999999,drag, velocity); //accel, decel, max speed
  mc->setDirection(direction);
  mc->setVelocity(velocity);
  mc->setAccelerating(false);
  e->addComponent(mc);

  Component *bpc = new Component(constants::BOUNCEPROJECTILE);
  e->addComponent(bpc);
  Component *dc = new Component(constants::DEADLY);
  e->addComponent(dc);
  CollidableComponent *colc = new CollidableComponent(e->getXY());
  e->addComponent(colc);



  em->addEntity(e);


}

void EntityCreator::createFinish(sf::Vector2f xy) {
  Entity *e = new Entity(em->getNewID());
  e->setXY(xy);
  e->setBoundingBox(new sf::FloatRect(xy.x-25, xy.y-25, 50, 50));
  Component *fc = new Component(constants::FINISH_COMP);
  e->addComponent(fc);

  sf::Sprite *sprite = new sf::Sprite();
  sprite->setTexture(*texture_table[WALL]);
  sprite->setOrigin(25,25);
  GraphicsComponent *gc = new GraphicsComponent(sprite);
  e->addComponent(gc);

  em->addEntity(e);
  
}
