#ifndef _LOGIC_SYSTEM_H_
#define _LOGIC_SYSTEM_H_


//need to include pretty much all components as well
#include "entityManager.h"
#include "constants.h"

class LogicSystem
{
public:
  LogicSystem(EntityManager *m, GameState state);
  ~LogicSystem();
  void update(float time);

private:

  void resolveCollisions(Entity* e);
  bool intersecting(sf::FloatRect *a, sf::FloatRect *b);


  EntityManager* manager;
  GameState state;
};

#endif
