#include "entity.h"


entity::entity(int i) :id(i){}

void entity::addComponent(component c){
  int componentType = 1;// c.getType();
  componentMap.insert(std::pair<int, component>(componentType,c));
}

bool entity::hasComponent(int c){
  std::map<int,component>::iterator it =  componentMap.find(c);
  return it != componentMap.end();
}

component* entity::getComponent(int type){
  std::map<int,component>::iterator it =  componentMap.find(type);
  return &(it->second); //return thes value of the key-value pair
}
