#include "entityCreator.h"
#include "global.h"
#include "typeConversion.h"
#include <string.h>
#include <cmath>
#include <iostream>


void EntityCreator::TextureManager::addTexture(std::string &file_name, int index){
    if (index >= 0) {
      index_to_name[index] = file_name;
  }
}
void EntityCreator::TextureManager::addTexture(const char *file_name, int index){
  std::string string_tmp = file_name;
  addTexture(string_tmp, index);
}
sf::Texture *EntityCreator::TextureManager::getTexture(std::string &file_name){
  return global()->gameEngine.resourceManager->getTexture(file_name);
}
sf::Texture *EntityCreator::TextureManager::getTexture(int index){
  if ( index_to_name.count(index) >= 1) {
    std::map<int,std::string>::iterator it = index_to_name.find(index);
    return getTexture(it->second);
  }
  return NULL;
}

EntityCreator::EntityCreator(EntityManager *em):em(em){
  textureManager.addTexture("resources/graphics/sprite/wall.png", WALL);
  textureManager.addTexture("resources/graphics/sprite/roy.png",PLAYER);
  textureManager.addTexture("resources/graphics/sprite/soldier.png",ENEMY);
  textureManager.addTexture("resources/graphics/sprite/bullet.png",BULLET);
  textureManager.addTexture("resources/graphics/sprite/grenade.png",GRENADE);
  textureManager.addTexture("resources/graphics/sprite/portal.png",EXIT);
  textureManager.addTexture("resources/graphics/sprite/box.png",BOX);
  textureManager.addTexture("resources/graphics/sprite/smoke.png",SMOKE);
  textureManager.addTexture("resources/graphics/sprite/trap.png",TRAP);
  textureManager.addTexture("resources/graphics/sprite/glass.png",GLASS);
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

void EntityCreator::create(constants::EntityType type, sf::Vector2f xy, std::string sprite_file_name) {
  if (type == constants::PLAYER) {
    this->createPlayer(xy, sprite_file_name);
  } else if (type == constants::WALL) {
    // this->createWall(xy, texture);
  } else if (type ==  constants::ENEMY_MOVING) {
    this->createMovingEnemy(xy, xy.x-200, xy.x+200, xy.y+200, xy.y-200, 0, 180, 90, 300, sprite_file_name);
  } else if (type == constants::FINISH) {
    this->createFinish(xy, sprite_file_name);
  }else if (type== constants::ENEMY_STATIC){
    this->createStaticEnemy(xy, 180, 90, 300, 90, sprite_file_name);
  } else if (type == constants::TRAP) {
    this->createTrap(xy, 10, true, sprite_file_name);
  }


  //not valid entityType
}

void EntityCreator::createPlayer(sf::Vector2f xy, std::string sprite_file_name) {
  Entity *e = new Entity(em->getNewID());
  e->setXY(xy);
  e->setBoundingBox(new sf::FloatRect(xy.x-12.5, xy.y-12.5, 25, 25));


  //////////////////this should probably be moved somewhere else
  //load texture
  // if(playerTexture == NULL){
  //   playerTexture = new sf::Texture();
  //   playerTexture->loadFromFile("resources/test.png");
  // }
  //create sprite
  sf::Sprite *sprite = new sf::Sprite();
  sf::Texture *texture = sprite_file_name.empty()? textureManager.getTexture(PLAYER):textureManager.getTexture(sprite_file_name);
  sprite->setTexture(* texture);
  sprite->setOrigin(25,25);
  sprite->setRotation(90.0f);
  ///////////////////////////////////////////////////////////

  GraphicsComponent *gc = new GraphicsComponent(sprite);

  MoveableComponent *mc;
  if(sprite_file_name == "resources/graphics/sprite/bonus/spaceship.png"){
    mc = new MoveableComponent(10000.0,0.0, 300.0); //accel, decel, max speed
    mc->setVelocity(0);
    mc->setAccelerating(false);
  }else{
    mc = new MoveableComponent(10000.0,80000.0, 300.0); //accel, decel, max speed
  }

  if(sprite_file_name == "resources/graphics/sprite/bonus/dinosaur.png" || sprite_file_name == "resources/graphics/sprite/bonus/lavaGuy.png"){
    Component *dr = new Component(constants::DONTROTATE);
    e->addComponent(dr);
  }
  CollidableComponent *colc = new CollidableComponent(e->getXY());
  PlayerComponent *pc = new PlayerComponent();

  // VisionComponent *vc = new VisionComponent(e->getXY(), 300, 270, 90);
  // e->addComponent(vc);

  e->addComponent(gc);
  e->addComponent(mc);
  e->addComponent(colc);
  e->addComponent(pc);

  em->addEntity(e);
  em->setPlayer(e);
}

void EntityCreator::createWall(sf::Vector2f xy, float width, float height, std::string sprite_file_name) {
  Entity *e = new Entity(em->getNewID());
  xy.x += width/2;
  xy.y += height/2;
  e->setXY(xy);
  e->setBoundingBox(new sf::FloatRect(xy.x-width/2, xy.y-height/2, width, height));

  //create sprite
  sf::Sprite *sprite = new sf::Sprite();
  sf::Texture *texture = sprite_file_name.empty()? textureManager.getTexture(WALL):textureManager.getTexture(sprite_file_name);
  texture->setRepeated(true);
  sprite->setTexture(* texture);
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

void EntityCreator::createGlass(sf::Vector2f xy, float width, float height, std::string sprite_file_name) {
  Entity *e = new Entity(em->getNewID());
  xy.x += width/2;
  xy.y += height/2;
  e->setXY(xy);
  e->setBoundingBox(new sf::FloatRect(xy.x-width/2, xy.y-height/2, width, height));

  //create sprite
  sf::Sprite *sprite = new sf::Sprite();
  sf::Texture *texture = sprite_file_name.empty()? textureManager.getTexture(GLASS):textureManager.getTexture(sprite_file_name);
  texture->setRepeated(true);
  sprite->setTexture(* texture);
  sprite->setOrigin(width/2, height/2);
  // sprite->getTexture()->setRepeated(true);
  sf::IntRect ir;

  ir.width = (int)width;
  ir.height = (int)height;
  sprite->setTextureRect(ir);
  ///////////////////////////////////////////////////////////

  GraphicsComponent *gc = new GraphicsComponent(sprite);
  Component *bmc = new Component(constants::BMOVEMENT);


  // VisionComponent *vc = new VisionComponent(e->getXY(), 300, rand()%360, 90);
  // e->addComponent(vc);


  e->addComponent(gc);
  e->addComponent(bmc);
  em->addEntity(e);

}

void EntityCreator::createBox(sf::Vector2f xy, std::string sprite_file_name) {
  Entity *e = new Entity(em->getNewID());
  e->setXY(xy);
  e->setBoundingBox(new sf::FloatRect(xy.x-25, xy.y-25, 50, 50));
  //create sprite
  sf::Sprite *sprite = new sf::Sprite();
  sf::Texture *texture = sprite_file_name.empty()? textureManager.getTexture(BOX):textureManager.getTexture(sprite_file_name);
  sprite->setTexture(*texture);
  sprite->setOrigin(25,25);
  ///////////////////////////////////////////////////////////
  GraphicsComponent *gc = new GraphicsComponent(sprite);
  e->addComponent(gc);

  Component *bmc = new Component(constants::BMOVEMENT);
  e->addComponent(bmc);
  BlockVisionComponent *bsc = new BlockVisionComponent(e->getXY(), 50, 50);
  e->addComponent(bsc);

  Component *kc = new Component(constants::KILLABLE);
  e->addComponent(kc);

  em->addEntity(e);

}

void EntityCreator::createMovingEnemy(sf::Vector2f xy, float xMin, float xMax, float yMin, float yMax, float moveDirection, float viewDirection, float viewAngle, float viewDistance, std::string sprite_file_name) {
  Entity *e = new Entity(em->getNewID());
  e->setXY(xy);
  e->setBoundingBox(new sf::FloatRect(xy.x-25, xy.y-25, 50, 50));
  //create sprite
  sf::Sprite *sprite = new sf::Sprite();
  sf::Texture *texture = sprite_file_name.empty()? textureManager.getTexture(ENEMY):textureManager.getTexture(sprite_file_name);
  sprite->setTexture(*texture);
  sprite->setOrigin(25,25);
  ///////////////////////////////////////////////////////////
  Component *ec = new Component(constants::ENEMY);
  e->addComponent(ec);

  GraphicsComponent *gc = new GraphicsComponent(sprite);
  e->addComponent(gc);

  MoveableComponent *mc = new MoveableComponent(1200.0,80000.0, 100.0); //accel, decel, max speed
  mc->setMaxXPos(xMax);
  mc->setMinXPos(xMin);
  mc->setMaxYPos(yMax);
  mc->setMinYPos(yMin);
  mc->setAccelerating(true);
  mc->setDirection(moveDirection);
  e->addComponent(mc);

  CollidableComponent *colc = new CollidableComponent(e->getXY());
  e->addComponent(colc);

  VisionComponent *vc = new VisionComponent(e->getXY(), viewDistance, viewDirection, viewAngle);

  e->addComponent(vc);

  Component *kc = new Component(constants::KILLABLE);
  e->addComponent(kc);
  //e->addComponent(conc);



  em->addEntity(e);

}
void EntityCreator::createStaticEnemy(sf::Vector2f xy, float viewDirection, float viewAngle, float viewDistance, float rotateAngle, std::string sprite_file_name) {
  Entity *e = new Entity(em->getNewID());
  e->setXY(xy);
  e->setBoundingBox(new sf::FloatRect(xy.x-25, xy.y-25, 50, 50));
  //create sprite
  sf::Sprite *sprite = new sf::Sprite();
  sf::Texture *texture = sprite_file_name.empty()? textureManager.getTexture(ENEMY):textureManager.getTexture(sprite_file_name);
  sprite->setTexture(*texture);
  sprite->setOrigin(25,25);
  ///////////////////////////////////////////////////////////
  Component *ec = new Component(constants::ENEMY);
  e->addComponent(ec);

  GraphicsComponent *gc = new GraphicsComponent(sprite);
  e->addComponent(gc);

  VisionComponent *vc = new VisionComponent(e->getXY(), viewDistance, viewDirection, viewAngle, viewDirection - rotateAngle/2, viewDirection + rotateAngle/2);

  e->addComponent(vc);

  Component *kc = new Component(constants::KILLABLE);
  e->addComponent(kc);



  em->addEntity(e);

}

void EntityCreator::createGrenade(sf::Vector2f xy, float direction, float velocity, float drag, std::string sprite_file_name){
  Entity *e = new Entity(em->getNewID());
  e->setXY(xy);
  e->setBoundingBox(new sf::FloatRect(xy.x-5, xy.y-5, 10, 10));
  // e->setXY(sf::Vector2f(xy.x+50*cos(direction*PI/180), xy.y+50*sin(direction*PI/180)));
  sf::Sprite *sprite = new sf::Sprite();
  sf::Texture *texture = sprite_file_name.empty()? textureManager.getTexture(GRENADE):textureManager.getTexture(sprite_file_name);
  sprite->setTexture(*texture);
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
  // Component *dc = new Component(constants::DEADLY);
  // e->addComponent(dc);
  CollidableComponent *colc = new CollidableComponent(e->getXY());
  e->addComponent(colc);

  TimerComponent *tc = new TimerComponent(2, constants::TSMOKESCREEN);
  e->addComponent(tc);



  em->addEntity(e);


}

void EntityCreator::createFinish(sf::Vector2f xy, std::string sprite_file_name) {
  Entity *e = new Entity(em->getNewID());
  e->setXY(xy);
  e->setBoundingBox(new sf::FloatRect(xy.x-25, xy.y-25, 50, 50));
  Component *fc = new Component(constants::FINISH_COMP);
  e->addComponent(fc);

  sf::Sprite *sprite = new sf::Sprite();
  sf::Texture *texture = sprite_file_name.empty()? textureManager.getTexture(EXIT):textureManager.getTexture(sprite_file_name);
  sprite->setTexture(*texture);
  sprite->setOrigin(25,25);
  GraphicsComponent *gc = new GraphicsComponent(sprite);
  e->addComponent(gc);

  em->addEntity(e);

}


void EntityCreator::createSmokeScreen(sf::Vector2f xy, std::string sprite_file_name){
  if(fmod(xy.x,50) < 25){
    xy.x = xy.x - fmod(xy.x,50);
  }else{
    xy.x = xy.x + 50- fmod(xy.x,50);
  }
  if(fmod(xy.y,50) < 25){
    xy.y = xy.y - fmod(xy.y,50);
  }else{
    xy.y = xy.y + 50- fmod(xy.y,50);
  }

  Entity *e = new Entity(em->getNewID());
  e->setXY(xy);

  float size = 50;

  e->setBoundingBox(new sf::FloatRect(xy.x-size/2, xy.y-size/2, size, size));
  sf::Sprite *sprite = new sf::Sprite();
  sf::Texture *texture = sprite_file_name.empty()? textureManager.getTexture(SMOKE):textureManager.getTexture(sprite_file_name);
  sprite->setTexture(*texture);
  sprite->setOrigin(size/2, size/2);
  GraphicsComponent *gc = new GraphicsComponent(sprite);
  e->addComponent(gc);

  BlockVisionComponent *bsc = new BlockVisionComponent(e->getXY(), size, size);
  e->addComponent(bsc);

  TimerComponent *tc = new TimerComponent(10, constants::TNOTHING);
  e->addComponent(tc);

  em->addEntity(e);


}

void EntityCreator::createTrap(sf::Vector2f xy, float time, bool isVisible, std::string sprite_file_name){
  Entity *e = new Entity(em->getNewID());
  e->setXY(xy);

  float size = 50;

  e->setBoundingBox(new sf::FloatRect(xy.x-size/2, xy.y-size/2, size, size));
  sf::Sprite *sprite = new sf::Sprite();
  sf::Texture *texture = sprite_file_name.empty()? textureManager.getTexture(TRAP):textureManager.getTexture(sprite_file_name);
  sprite->setTexture(*texture);
  sprite->setOrigin(size/2, size/2);
  GraphicsComponent *gc = new GraphicsComponent(sprite);
  e->addComponent(gc);

  TrapComponent *trc = new TrapComponent(isVisible, time);
  e->addComponent(trc);
  TimerComponent *tc = new TimerComponent(time, constants::TTRAP);
  e->addComponent(tc);

  em->addEntity(e);

}
void EntityCreator::createInventory(sf::Vector2f xy,  std::map<std::string, std::string> &item_list, int level, int time){

  Entity *e = new Entity(em->getNewID());

  //e->setXY(xy);
  InventoryComponent *ic = new InventoryComponent();
  ic->setLevelSign(level);
  ic->setTimerStartTime(time);
  std::map<std::string, std::string>::iterator it;
  for(it = item_list.begin(); it != item_list.end(); it++) {
    if (it->first == "common" ) {
      ic->addItem(InventoryComponent::INV_BULLET_COMMON, typeconvert::string2int(it->second));
    }
    if (it->first == "smoke" ) {
      ic->addItem(InventoryComponent::INV_BULLET_SMOKE, typeconvert::string2int(it->second));
    }
  }

  e->addComponent(ic);

  em->addEntity(e);
  em->setInventory(e);

}

void EntityCreator::createBullet(sf::Vector2f xy, float direction, float velocity, std::string sprite_file_name){
  Entity *e = new Entity(em->getNewID());
  e->setXY(xy);
  e->setBoundingBox(new sf::FloatRect(xy.x-3, xy.y-5, 6, 10));
  // e->setXY(sf::Vector2f(xy.x+50*cos(direction*PI/180), xy.y+50*sin(direction*PI/180)));
  sf::Sprite *sprite = new sf::Sprite();
  sf::Texture *texture = sprite_file_name.empty()? textureManager.getTexture(BULLET):textureManager.getTexture(sprite_file_name);
  sprite->setTexture(*texture);
  sprite->setOrigin(6,6);
  sprite->setRotation(90.0);
  sprite->rotate(-1*direction);


  GraphicsComponent *gc = new GraphicsComponent(sprite);
  e->addComponent(gc);
  MoveableComponent *mc = new MoveableComponent(999999,0, velocity); //accel, decel, max speed
  mc->setDirection(direction);
  mc->setVelocity(velocity);
  mc->setAccelerating(false);
  e->addComponent(mc);

  Component *bpc = new Component(constants::BULLETPROJECTILE);
  e->addComponent(bpc);
  Component *dc = new Component(constants::DEADLY);
  e->addComponent(dc);
  CollidableComponent *colc = new CollidableComponent(e->getXY());
  e->addComponent(colc);




  em->addEntity(e);
}
void EntityCreator::createBouncingEnemy(sf::Vector2f xy, float direction, float speed, float killable, float size, std::string sprite_file_name){
  Entity *e = new Entity(em->getNewID());
  e->setXY(xy);
  e->setBoundingBox(new sf::FloatRect(xy.x-size/2, xy.y-size/2, size, size));
  sf::Sprite *sprite = new sf::Sprite();
  sf::Texture *texture = sprite_file_name.empty()? textureManager.getTexture(GRENADE):textureManager.getTexture(sprite_file_name);
  sprite->setTexture(*texture);
  sprite->setOrigin(size/4*2.5,size/4*2.5);
  sprite->setRotation(-1*direction +90);


  GraphicsComponent *gc = new GraphicsComponent(sprite);
  e->addComponent(gc);
  MoveableComponent *mc = new MoveableComponent(999999,0, speed); //accel, decel, max speed
  mc->setDirection(direction);
  mc->setVelocity(speed);
  mc->setAccelerating(false);
  e->addComponent(mc);

  Component *bpc = new Component(constants::BOUNCEPROJECTILE);
  e->addComponent(bpc);

  CollidableComponent *colc = new CollidableComponent(e->getXY());
  e->addComponent(colc);

  TrapComponent *trc = new TrapComponent(true, -1);
  e->addComponent(trc);

  if(killable > 0){
    Component *kc = new Component(constants::KILLABLE);
    e->addComponent(kc);
  }

  Component *bmc = new Component(constants::BMOVEMENT);
  e->addComponent(bmc);




  em->addEntity(e);
}
