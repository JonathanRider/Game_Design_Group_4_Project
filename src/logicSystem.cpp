#include "logicSystem.h"
#include "allComponents.h"
#include <math.h>
#include <iostream>


LogicSystem::LogicSystem(EntityManager *m, GameState s)
  :manager(m), state(s){}

void LogicSystem::update(float time){


  //for each component type that we want to do stuff with


  std::list<Entity>* eList = manager->getEntityList();
  std::list<Entity>::iterator iterator;
  for (iterator = eList->begin(); iterator != eList->end(); ++iterator) {
    if(iterator->hasComponent(MOVEABLE)){
      MoveableComponent *mp = (MoveableComponent*)iterator->getComponent(MOVEABLE);
      if(mp->getAccelerating()){
        mp->changeVelocity(mp->getAcceleration()*time);
      }else{
        mp->changeVelocity(-1*mp->getDeceleration()*time);
      }


      float v = mp->getVelocity();
      float d = mp->getDirection();
      float dx = time*(v*cos(d*PI/180.0));
      float dy = -time*(v*sin(d*PI/180.0));

      sf::Vector2f newXY = sf::Vector2f(iterator->getXY().x + dx, iterator->getXY().y + dy);
      iterator->setXY(newXY);
    }
  }




}
