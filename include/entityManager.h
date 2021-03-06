#ifndef _ENTITY_MANAGER_H_
#define _ENTITY_MANAGER_H_

#include "entity.h"
#include <list>

class EntityManager
{
public:
  EntityManager(){nextID = 0;}
  ~EntityManager();

  void addEntity(Entity *e);
  void removeEntity(int id);
  void removeEntity(Entity *e);
  void clearAll();
  Entity *findEntity(int id);
  std::list<Entity *>* getEntityList();

  int getNewID();

  Entity* getPlayer() { return  player_entity;}
  void setPlayer(Entity *e) { player_entity = e;}
  Entity* getInventory() { return  inventory_entity;}
  void setInventory(Entity *e) { inventory_entity = e;}

private:
  std::list<Entity *> entityList;
  int nextID;

  Entity *player_entity; // it points to the player entity for easy reference
  Entity *inventory_entity; // it points to the inventory entity for easy reference

};



#endif
