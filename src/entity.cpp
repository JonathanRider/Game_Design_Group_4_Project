#include "entity.h"


Entity::Entity(int i) :id(i){}

void Entity::addComponent(Component* c){
  ComponentType componentType =  c->getType();
  componentMap.insert(std::pair<ComponentType, Component*>(componentType,c));
}

bool Entity::hasComponent(ComponentType type){
  std::map<ComponentType,Component*>::iterator it =  componentMap.find(type);
  return it != componentMap.end();
}

Component* Entity::getComponent(ComponentType type){
  std::map<ComponentType,Component*>::iterator it =  componentMap.find(type);
  return (it->second); //return thes value of the key-value pair
}

void Entity::setXY(sf::Vector2f newXY){
  xy.x = newXY.x;
  xy.y = newXY.y;
  if(this->hasComponent(COLLIDABLE)){
    CollidableComponent *cc = (CollidableComponent*)this->getComponent(COLLIDABLE);
    cc->moveTo(xy);

  }
}
