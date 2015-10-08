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
          if(origBB->left < otherBB->left){
            //need to move to left
            e->setXY(sf::Vector2f(otherBB->left - origBB->width + origBB->width/2, e->getXY().y ));
            //origBB->left = otherBB->left - origBB->width;
          }
          if(origBB->left > otherBB->left){
            //need to move to the right
            e->setXY(sf::Vector2f(otherBB->left + otherBB->width + origBB->width/2, e->getXY().y ));
            // origBB->left = otherBB->left + otherBB->width;
          }
          if(origBB->top < otherBB->top){
            //need to move up
            e->setXY(sf::Vector2f(e->getXY().x, otherBB->top - origBB->height + origBB->height/2));
            // origBB->top = otherBB->top - origBB->height;
          if(origBB->top > otherBB->top){
            //need to move down
            e->setXY(sf::Vector2f(e->getXY().x, otherBB->top +otherBB->height + origBB->height/2));
            // origBB->top = otherBB->top + otherBB->height;
          }
          }

        }
      }
    }


  }
}
