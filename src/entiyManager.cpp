#include "entityManager.h"

int EntityManager::getNewID(){
  int curID = nextID;
  nextID ++;
  return curID;
}

void EntityManager::addEntity(Entity e){
  entityList.push_back(e);
}

std::list<Entity>* EntityManager::getEntityList(){
  return &entityList;
}
