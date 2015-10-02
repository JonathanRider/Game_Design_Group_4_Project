#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include "entity.h"
#include <list>

class entityManager
{
public:
  entityManager();
  ~entityManager();

  void addEntity(entity e);
  void removeEntity(int id);
  entity findEntity(int id);
  std::list<entity>* getEntityList();

  int getNewID();

private:
  std::list<entity> entityList;
  int nextId;

};



#endif
