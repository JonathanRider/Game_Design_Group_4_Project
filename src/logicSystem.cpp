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
          }
          if(origBB->top < otherBB->top){
            //need to move down
            e->setXY(sf::Vector2f(e->getXY().x, otherBB->top +otherBB->height + origBB->height/2));
            // origBB->top = otherBB->top + otherBB->height;
          }

        }
      }
    }


  }
}

bool LogicSystem::intersecting(sf::FloatRect *a, sf::FloatRect *b){

    // Rectangles with negative dimensions are allowed, so we must handle them correctly

    // // Compute the min and max of the first rectangle on both axes
    // float r1MinX = std::min(a->left, (a->left + a->width));
    // float r1MaxX = std::max(a->left, (a->left + a->width));
    // float r1MinY = std::min(a->top, (a->top + a->height));
    // float r1MaxY = std::max(a->top, (a->top + a->height));
    //
    // // Compute the min and max of the second rectangle on both axes
    // float r2MinX = std::min(b->left, (b->left + b->width));
    // float r2MaxX = std::max(b->left, (b->left + b->width));
    // float r2MinY = std::min(b->top, (b->top + b->height));
    // float r2MaxY = std::max(b->top, (b->top + b->height));

    // Compute the intersection boundaries
    float interLeft   = std::max(a->left, b->left);
    float interTop    = std::max(a->top, b->top);
    float interRight  = std::min(a->left + a->width, b->left + b->width);
    float interBottom = std::min(a->top + a->height, b->top + b->height);
    std::cout << "horizontal  " << interLeft << "  " << interRight  << "  Vertical: " << interTop << "  " <<interBottom << std::endl;

    // If the intersection is valid (positive non zero area), then there is an intersection
    if ((interLeft < interRight) && (interTop < interBottom))
    {
        return true;
    }
    else
    {
        return false;
    }
}
