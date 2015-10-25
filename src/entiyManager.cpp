#include "entityManager.h"

EntityManager::~EntityManager(){
    std::list<Entity*>::iterator iterator;
    for (iterator = entityList.begin(); iterator != entityList.end(); ++iterator) {
      delete (*iterator);
    }
}

int EntityManager::getNewID(){
  int curID = nextID;
  nextID ++;
  return curID;
}

void EntityManager::addEntity(Entity *e){
  entityList.push_back(e);
}

void EntityManager::removeEntity(int id){
  std::list<Entity*>::iterator iterator;
  for (iterator = entityList.begin(); iterator != entityList.end(); ++iterator) {
    if ((*iterator)->getID() == id) {
      Entity *e = (*iterator);
      entityList.erase (iterator);
      delete e;
      return;
    }
  }
}
void EntityManager::removeEntity(Entity *e){
  entityList.remove(e);
  delete e;
}

std::list<Entity*>* EntityManager::getEntityList(){
  return &entityList;
}

Entity *EntityManager::findEntity(int id) {

  std::list<Entity*>::iterator iterator;
  for (iterator = entityList.begin(); iterator != entityList.end(); ++iterator) {
    if ((*iterator)->getID() == id) {
      return *iterator;
    }
  }
}
