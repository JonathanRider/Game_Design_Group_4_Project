#include "entityManager.h"

EntityManager::EntityManager(){}


void EntityManager::addEntity(Entity e){
  entityList.push_back(e);
}

std::list<Entity>* EntityManager::getEntityList(){
  return &entityList;
}
