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

Entity *EntityManager::findEntity(int id) {

  std::list<Entity>::iterator iterator;
  for (iterator = entityList.begin(); iterator != entityList.end(); ++iterator) {
    if (iterator->getID() == id) {
      return &(*iterator);
    }
  }
}
