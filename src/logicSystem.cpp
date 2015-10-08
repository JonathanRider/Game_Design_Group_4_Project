#include "logicSystem.h"
#include "allComponents.h"
#include <cmath>
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
      if(iterator->hasComponent(COLLIDABLE)){
        this->resolveCollisions(&(*iterator));
        //CollidableComponent *cc = (CollidableComponent*)iterator->getComponent(MOVEABLE);
      }
    }
  }
}

void LogicSystem::resolveCollisions(Entity *e){
  CollidableComponent *occ = (CollidableComponent*)e->getComponent(COLLIDABLE);
  sf::FloatRect *origBB = occ->getBoundingBox();

  std::list<Entity>* eList = manager->getEntityList();
  std::list<Entity>::iterator iterator;
  for (iterator = eList->begin(); iterator != eList->end(); ++iterator) {
    if(e->getID() != iterator->getID()){
      if(iterator->hasComponent(COLLIDABLE)){
        CollidableComponent *cc = (CollidableComponent*)iterator->getComponent(COLLIDABLE);
        sf::FloatRect *otherBB = cc->getBoundingBox();
        if(origBB->intersects(*otherBB)){
          MoveableComponent *mc = (MoveableComponent*)e->getComponent(MOVEABLE);
          float reverseDirection = fmod((mc->getDirection() + 180),360);

          float xRatio = cos(reverseDirection*PI/180.0);
          float yRatio = sin(reverseDirection*PI/180.0);

          float xOverlap;
          if(origBB->left < otherBB->left){
            //original is on the left
            xOverlap = (origBB->width) - (otherBB->left - origBB->left);
          }else{
            //original is on the right
            xOverlap = (otherBB->width) - (origBB->left - otherBB->left);
          }

          float yOverlap;
          if(origBB->top < otherBB->top){
            //original on top
            yOverlap = origBB->height - (otherBB->top - origBB->top);
          }else{
            //original on bottom
            yOverlap = otherBB->height - (origBB->top - otherBB->top);
          }

          //find minimum distance to get out of the other object
          float distance = std::min(fabs(yOverlap/yRatio), fabs(xOverlap/xRatio));
          float dy = -distance*yRatio;
          float dx = distance*xRatio;
          sf::Vector2f newXY = sf::Vector2f(e->getXY().x + dx, e->getXY().y + dy);
          e->setXY(newXY);

          //code to allow sliding along the collisions
          //move just x
          e->setXY(sf::Vector2f(e->getXY().x -dx, e->getXY().y));
          //reset if it intersects
          if(origBB->intersects(*otherBB)){
            e->setXY(newXY);
          }else{
            newXY.x = e->getXY().x;
            newXY.y = e->getXY().y;
          }
          e->setXY(sf::Vector2f(e->getXY().x, e->getXY().y - dy));
          if(origBB->intersects(*otherBB)){
            e->setXY(newXY);
          }
        }
      }
    }
  }
}
