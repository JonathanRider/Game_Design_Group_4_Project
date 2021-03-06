#ifndef _LOGIC_SYSTEM_H_
#define _LOGIC_SYSTEM_H_


//need to include pretty much all components as well
#include "entityManager.h"
#include "levelCreator.h"


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
  LogicSystem(EntityManager *m, LevelCreator *lc);
  ~LogicSystem();
  void update(float time);

  void receiveInput(constants::Input input, void *extra_data);


  constants::GameState* state;
private:

  bool playerVisible;
  void resolveCollisions(Entity* e);
  void resolveTimer(Entity* e);


  void updateVisionCones(float time);

  sf::Vector2f interSectLineAndRects(sf::Vector2f origin, sf::Vector2f endpoint, constants::ComponentType type);

  std::list<anglePoint>* sortPointsByAngle(Entity *e);
  bool addAnglePoints(Entity *e, std::list<anglePoint>* result,  sf::Vector2f v, bool cornerTop, bool cornerLeft);
  void addAnglePointsMidWall(Entity *e, std::list<anglePoint>* result,  sf::Vector2f v,bool horizontal);

  static sf::Vector2f intersectLines(sf::Vector2f a1, sf::Vector2f a2, sf::Vector2f b1, sf::Vector2f b2);
  static float squareDist(sf::Vector2f a, sf::Vector2f b);
  static float calculateAngle(sf::Vector2f a, sf::Vector2f b);
  static float calculateShootingSpeed(float distance, float deceleration);

  EntityManager* manager;
  LevelCreator* lCreator;
};

#endif
