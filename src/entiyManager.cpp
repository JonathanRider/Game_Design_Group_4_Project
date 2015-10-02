#include "entityManager.h"

entityManager::entityManager(){}


void entityManager::addEntity(entity e){
  entityList.push_back(e);
}

std::list<entity>* entityManager::getEntityList(){
  return &entityList;
}
