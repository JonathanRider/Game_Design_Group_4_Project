#include "entity.h"


Entity::Entity(int i) :id(i){}

Entity::~Entity(){
  std::map<constants::ComponentType,Component*>::iterator it;
  for( it = componentMap.begin(); it != componentMap.end(); it++) {
      delete it->second;
  }
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

void Entity::setXY(sf::Vector2f newXY){
  xy.x = newXY.x;
  xy.y = newXY.y;
  if(this->hasComponent(constants::COLLIDABLE)){
    CollidableComponent *cc = (CollidableComponent*)this->getComponent(constants::COLLIDABLE);
    cc->moveTo(xy);
  }
  if(this->hasComponent(constants::BVISION)){
    BlockVisionComponent *bsc = (BlockVisionComponent*)this->getComponent(constants::BVISION);
    bsc->moveTo(xy);
  }

}
