#ifndef _LOGIC_SYSTEM_H_
#define _LOGIC_SYSTEM_H_


//need to include pretty much all components as well
#include "entityManager.h"
#include "config.h"


struct anglePoint {
  anglePoint() :before(false), after(false), collision(true){}
  sf::Vector2f point;
  float angle;
  bool before;
  bool after;
  bool collision;
};

class LogicSystem
{
public:
  LogicSystem(EntityManager *m);
  ~LogicSystem();
  void update(float time);


private:

  void resolveCollisions(Entity* e);
  void moveEntity(Entity* e, float time);
  void updateVisionCones(float time);

  sf::Vector2f interSectLineAndRects(sf::Vector2f origin, sf::Vector2f endpoint, ComponentType type);

  std::list<anglePoint>* sortPointsByAngle(Entity *e);
  void addAnglePoints(Entity *e, std::list<anglePoint>* result,  sf::Vector2f v, bool cornerTop, bool cornerLeft);
  void addAnglePointsMidWall(Entity *e, std::list<anglePoint>* result,  sf::Vector2f v,bool horizontal);

  static sf::Vector2f intersectLines(sf::Vector2f a1, sf::Vector2f a2, sf::Vector2f b1, sf::Vector2f b2);
  static float squareDist(sf::Vector2f a, sf::Vector2f b);
  static float calculateAngle(sf::Vector2f a, sf::Vector2f b);

  void moveEnemies(Entity *e);

  EntityManager* manager;
};

#endif
