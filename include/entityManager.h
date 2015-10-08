#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include "entity.h"
#include <list>

class EntityManager
{
public:
  EntityManager(){nextID = 0;}
  ~EntityManager();

  void addEntity(Entity e);
  void removeEntity(int id);
  Entity findEntity(int id);
  std::list<Entity>* getEntityList();

  int getNewID();

private:
  std::list<Entity> entityList;
  int nextID;

};



#endif
