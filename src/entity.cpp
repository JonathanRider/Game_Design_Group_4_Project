#include "entity.h"
#include <cmath>
#include <iostream>
Entity::Entity(int i) :id(i){
  boundingBox = new sf::FloatRect();
}

Entity::~Entity(){
  std::map<constants::ComponentType,Component*>::iterator it;
  for( it = componentMap.begin(); it != componentMap.end(); it++) {
      delete it->second;
  }
  delete boundingBox;
}

void Entity::addComponent(Component* c){
  constants::ComponentType componentType =  c->getType();
  componentMap.insert(std::pair<constants::ComponentType, Component*>(componentType,c));
}

bool Entity::hasComponent(constants::ComponentType type){
  std::map<constants::ComponentType,Component*>::iterator it =  componentMap.find(type);
  return it != componentMap.end();
}

Component* Entity::getComponent(constants::ComponentType type){
  std::map<constants::ComponentType,Component*>::iterator it =  componentMap.find(type);
  return (it->second); //return thes value of the key-value pair
}
bool Entity::getComponent(constants::ComponentType type, Component * &component){
  //This function is safe. It will give the correct component only if this component exists.
  std::map<constants::ComponentType,Component*>::iterator it =  componentMap.find(type);
  if (it == componentMap.end()){
    component = NULL;
    return false;
  }
  else {
    component = it->second;
    return true;
  }
}

void Entity::setXY(sf::Vector2f newXY){
  xy.x = newXY.x;
  xy.y = newXY.y;


  if(this->hasComponent(constants::BVISION)){
    BlockVisionComponent *bsc = (BlockVisionComponent*)this->getComponent(constants::BVISION);
    bsc->moveTo(xy);
  }


  boundingBox->top = xy.y - boundingBox->height/2;
  boundingBox->left = xy.x - boundingBox->width/2;


}
void Entity::move(float time){
  Component *c;
  if (this->getComponent(constants::MOVEABLE, c)) {
    MoveableComponent *mp = (MoveableComponent*) c;
    if(mp->getAccelerating()){
      mp->changeVelocity(mp->getAcceleration()*time);
    }else{
      mp->changeVelocity(-1*mp->getDeceleration()*time);
    }
    float v = mp->getVelocity();
    float d = mp->getDirection();
    float dx = time*(v*cos(d*PI/180.0));
    float dy = -time*(v*sin(d*PI/180.0));

    sf::Vector2f newXY = sf::Vector2f(this->getXY().x + dx, this->getXY().y + dy);
    this->setXY(newXY);

    if (this->getComponent(constants::ENEMY, c)) {
      if(mp->getMinXPos() !=mp->getMaxXPos()){
        if (this->getXY().x < mp->getMinXPos()){
          mp->setDirection(mp->getDirection() + 180);
          this->setXY(sf::Vector2f(mp->getMinXPos()+0.01, xy.y));
        }else if (this->getXY().x > mp->getMaxXPos()){
          mp->setDirection(mp->getDirection() + 180);
          this->setXY(sf::Vector2f(mp->getMaxXPos()-0.01, xy.y));
        }
      }
      if(mp->getMinYPos() != mp->getMaxYPos()){
        if(this->getXY().y < mp->getMinYPos()) {
          mp->setDirection(mp->getDirection() + 180);
          this->setXY(sf::Vector2f(xy.x, mp->getMinYPos()+0.01));
        }else if(this->getXY().y > mp->getMaxYPos()) {
          mp->setDirection(mp->getDirection() + 180);
          this->setXY(sf::Vector2f(xy.x, mp->getMaxYPos()-0.01));
        }
      }
    }
  }


}

void Entity::receiveInput(constants::Input input, void *extra_data){
  Component *c;
  if (this->getComponent(constants::MOVEABLE, c)) {
    MoveableComponent *mp = (MoveableComponent*) c;

    switch (input) {
      case constants::INPUT_LEFT_UP:
        mp->setDirection(135.0);
        mp->setAccelerating(true);
      break;
      case constants::INPUT_UP:
        mp->setDirection(90.0);
        mp->setAccelerating(true);
      break;
      case constants::INPUT_RIGHT_UP:
        mp->setDirection(45.0);
        mp->setAccelerating(true);
      break;
      case constants::INPUT_LEFT:
        mp->setDirection(180.0);
        mp->setAccelerating(true);
      break;
      case constants::INPUT_RIGHT:
        mp->setDirection(0.0);
        mp->setAccelerating(true);
      break;
      case constants::INPUT_LEFT_DOWN:
        mp->setDirection(225.0);
        mp->setAccelerating(true);
      break;
      case constants::INPUT_RIGHT_DOWN:
        mp->setDirection(315.0);
        mp->setAccelerating(true);
      break;
      case constants::INPUT_DOWN:
        mp->setDirection(270.0);
        mp->setAccelerating(true);
      break;
      default:
        mp->setAccelerating(false);
      break;
    }

  }
  if (this->getComponent(constants::INVENTORY, c)) {
    InventoryComponent *ip = (InventoryComponent*) c;
    switch (input) {
      case constants::INPUT_PREVITEM:
        ip->prevItem();
        break;
      case constants::INPUT_NEXTITEM:
        ip->nextItem();
        break;
      default:
        break;
    }
  }
  if (this->getComponent(constants::PLAYERC, c) && extra_data != NULL){
    this->getComponent(constants::GRAPHICS, c);
    GraphicsComponent * gp = (GraphicsComponent *)c;
    sf::Vector2f * mouse_position = (sf::Vector2f *) extra_data;
    gp->rotateTo(*mouse_position);
  }
}
