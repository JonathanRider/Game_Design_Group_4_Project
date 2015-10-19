#include "logicSystem.h"
#include "allComponents.h"
#include "collisionDetection.h"
#include <cmath>
#include <iostream>
#include <unistd.h>

bool print = false;
LogicSystem::LogicSystem(EntityManager *m, GameState s)
  :manager(m), state(s){}

void LogicSystem::update(float time){
  //for each component type that we want to do stuff with


  std::list<Entity>* eList = manager->getEntityList();
  std::list<Entity>::iterator iterator;

  for (iterator = eList->begin(); iterator != eList->end(); ++iterator) {
    if(iterator->hasComponent(MOVEABLE)){
      this->moveEntity(&(*iterator), time);
      if(iterator->hasComponent(ENEMY)) {
        this->moveEnemies(&(*iterator));
      }
      if(iterator->hasComponent(COLLIDABLE)){
        this->resolveCollisions(&(*iterator));
      }
    }
  }
  this->updateVisionCones(time);

}

void LogicSystem::moveEntity(Entity* e, float time) {
  MoveableComponent *mp = (MoveableComponent*)e->getComponent(MOVEABLE);
  if(mp->getAccelerating()){
    mp->changeVelocity(mp->getAcceleration()*time);
  }else{
    mp->changeVelocity(-1*mp->getDeceleration()*time);
  }
  float v = mp->getVelocity();
  float d = mp->getDirection();
  float dx = time*(v*cos(d*PI/180.0));
  float dy = -time*(v*sin(d*PI/180.0));

  sf::Vector2f newXY = sf::Vector2f(e->getXY().x + dx, e->getXY().y + dy);
  e->setXY(newXY);
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

          //hits exactly on corner, only going to happen if sliding along a wall
          if(fabs(yOverlap/yRatio)== fabs(xOverlap/xRatio)){
            //prevent it from getting stuck on the wall
            if(occ->getSlideDirection() == 1){
              xRatio = 0;
            }else{
              yRatio = 0;
            }
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
            occ->setSlideDirection(1); //x direction
            e->setXY(newXY);
          }else{
            newXY.x = e->getXY().x;
            newXY.y = e->getXY().y;
          }

          //move just y
          e->setXY(sf::Vector2f(e->getXY().x, e->getXY().y - dy));
          //reset if it intersects
          if(origBB->intersects(*otherBB)){
            e->setXY(newXY);
          }else{
            occ->setSlideDirection(-1); //y direction
          }
        }else{
          occ->setSlideDirection(0);//not sliding
        }
      }
    }
  }
}


void LogicSystem::updateVisionCones(float time){
  //Let's get the player entity and its bounding box
  Entity player_entity = manager->getPlayer();
  CollidableComponent * player_cp = (CollidableComponent *) player_entity.getComponent(COLLIDABLE);
  sf::FloatRect *player_box = player_cp->getBoundingBox();

  std::list<Entity>* eList = manager->getEntityList();
  std::list<Entity>::iterator iterator;
  for (iterator = eList->begin(); iterator != eList->end(); ++iterator) {
    if(iterator->hasComponent(VISION)){
      VisionComponent *vc = (VisionComponent*)iterator->getComponent(VISION);
      //first, we need to sort all the vision blocking points by angle, starting with the start angle

      std::list<anglePoint> *pointList = this->sortPointsByAngle(&(*iterator));

      sf::VertexArray *tFan = vc->getTriangles();
      tFan->resize(pointList->size()*2 + vc->getConeAngle()*vc->getVisionResolution() +3); //make it larger than it probably needs to be, can shrink afterwards
      (*tFan)[0].position = iterator->getXY();
      std::list<anglePoint>::iterator i;

      int counter = 1;
      float prevAngle = -1*vc->getVisionResolution() + vc->getDirection() - vc->getConeAngle()/2;
      bool twoPasses = false;
      float lowAngle = vc->getDirection() - vc->getConeAngle()/2;
      float highAngle = vc->getDirection() + vc->getConeAngle()/2;
      if(highAngle > 360){
        twoPasses = true;
        highAngle -= 360;
      }
      if(lowAngle < 0){
        twoPasses = true;
        lowAngle += 360;
      }

      if(!twoPasses){
        bool first = true;
        for(i = pointList->begin(); i != pointList->end(); ++i){
          if( (i->angle <=  highAngle && i->angle >= lowAngle )){
            sf::Vector2f point = this->interSectLineAndRects(iterator->getXY(), i->point, BVISION);
            float angle = this->calculateAngle(iterator->getXY(), point);
            while(angle > prevAngle + vc->getVisionResolution() && !i->collision && !first){
              prevAngle += vc->getVisionResolution();
              (*tFan)[counter].position = sf::Vector2f(iterator->getXY().x + vc->getLength()*cos(prevAngle*PI/180), iterator->getXY().y + vc->getLength()*sin(prevAngle*PI/180));
              counter++;
            }
            first = false;
            (*tFan)[counter].position = point;
            counter++;
            prevAngle = i->angle;
          }
        }


      }else{
        prevAngle = -1*vc->getVisionResolution() + lowAngle;
        for(i = pointList->begin(); i != pointList->end(); ++i){

          if(  i->angle >= lowAngle){

            sf::Vector2f point = this->interSectLineAndRects(iterator->getXY(), i->point, BVISION);
            float angle = this->calculateAngle(iterator->getXY(), point);
            while(angle > prevAngle + vc->getVisionResolution() && (!i->collision)){
              prevAngle += vc->getVisionResolution();
              (*tFan)[counter].position = sf::Vector2f(iterator->getXY().x + vc->getLength()*cos(prevAngle*PI/180), iterator->getXY().y + vc->getLength()*sin(prevAngle*PI/180));
              counter++;
            }
            (*tFan)[counter].position = point;
            counter++;
            prevAngle = i->angle;
          }
        }

        for(i = pointList->begin(); i != pointList->end(); ++i){

          if(  i->angle <= highAngle){

            sf::Vector2f point = this->interSectLineAndRects(iterator->getXY(), i->point, BVISION);
            float angle = this->calculateAngle(iterator->getXY(), point);
            while(angle > prevAngle + vc->getVisionResolution() && (!i->collision)){
              prevAngle += vc->getVisionResolution();
              (*tFan)[counter].position = sf::Vector2f(iterator->getXY().x + vc->getLength()*cos(prevAngle*PI/180), iterator->getXY().y + vc->getLength()*sin(prevAngle*PI/180));
              counter++;
            }
            (*tFan)[counter].position = point;
            counter++;
            prevAngle = i->angle;
          }
        }
      }

      tFan->resize(counter); //shrink it down to the right size

      //Check whether the vision has caught our player
      vc->setAlert(false);
      for(int i =1; i < tFan->getVertexCount()-1 ; i++){
        if (collision::triIntersectRect((*tFan)[0].position, (*tFan)[i].position, (*tFan)[i+1].position, *player_box)) {
          vc->setAlert(true);
          break;
        }
      }


    }
  }
}

//takes a line segment and returns the closest point it intersects a rectangle. The endpoint otherwise
sf::Vector2f LogicSystem::interSectLineAndRects(sf::Vector2f origin, sf::Vector2f endpoint, ComponentType type){
  sf::Vector2f currentMinPoint = endpoint;

  int bottom = (origin.y > endpoint.y);
  int right = (origin.x > endpoint.x);

  float minLength = squareDist(origin, endpoint);  //(origin.x - endpoint.x)*(origin.x - endpoint.x) + (origin.y - endpoint.y)*(origin.y - endpoint.y);
  if(type = BVISION){
    std::list<Entity>* eList = manager->getEntityList();
    std::list<Entity>::iterator iterator;
    for (iterator = eList->begin(); iterator != eList->end(); ++iterator) {
      if(iterator->hasComponent(BVISION)){
        BlockVisionComponent *vc = (BlockVisionComponent*)iterator->getComponent(BVISION);


        //depending on which direction the ray is coming from, we only need to look at 3 points of the rectangle.
        sf::Vector2f p1;
        sf::Vector2f p2;
        sf::Vector2f p3;
        if(bottom){
          if(right){
            p1 = vc->getBottomRight();
            p2 = vc->getBottomLeft();
            p3 = vc->getTopRight();
          }else{
            p1 = vc->getBottomLeft();
            p2 = vc->getBottomRight();
            p3 = vc->getTopLeft();
          }
        }else{
          if(right){
            p1 = vc->getTopRight();
            p2 = vc->getTopLeft();
            p3 = vc->getBottomRight();
          }else{
            p1 = vc->getTopLeft();
            p2 = vc->getTopRight();
            p3 = vc->getBottomLeft();
          }
        }


        sf::Vector2f ip = intersectLines(origin, endpoint, p1, p2);
        //check to see if it the closest intersection
        if(squareDist(origin, ip) < minLength- 0.01){
          currentMinPoint.x = ip.x;
          currentMinPoint.y = ip.y;
          minLength = squareDist(origin, ip);
        }
        ip = intersectLines(origin, endpoint, p1, p3);
        if(squareDist(origin, ip) < minLength- 0.01){
          currentMinPoint.x = ip.x;
          currentMinPoint.y = ip.y;
          minLength = squareDist(origin, ip);
        }
      }
    }
  }
  return currentMinPoint;
}

//find the intersection point between 2 lines.
//If no intersection, returns the endpoint of the first line
sf::Vector2f LogicSystem::intersectLines(sf::Vector2f a1, sf::Vector2f a2, sf::Vector2f b1, sf::Vector2f b2){
  sf::Vector2f returnVal = a2;
  //math to find the determinant
  float A1 = a2.y - a1.y;
  float A2 = b2.y - b1.y;
  float B1 = a1.x - a2.x;
  float B2 = b1.x - b2.x;
  float C1 = A1*a1.x + B1*a1.y;
  float C2 = A2*b1.x + B2*b1.y;

  float det = A1*B2 - A2*B1;
  if(det == 0){
    //parallel lines
    return returnVal;
  }
  float x = (B2*C1 - B1*C2)/det;
  float y = (A1*C2 - A2*C1)/det;
  //check to see if it is on the line
  if(std::min(a1.x, a2.x) <= x + 0.001 && std::max(a1.x, a2.x)+ 0.001 >= x && std::min(a1.y, a2.y) <= y+ 0.001 && std::max(a1.y, a2.y)+ 0.001 >= y
      && std::min(b1.x, b2.x) <= x+ 0.001 && std::max(b1.x, b2.x)+ 0.001 >= x && std::min(b1.y, b2.y) <= y+ 0.001 && std::max(b1.y, b2.y)+ 0.001 >= y){

    returnVal = sf::Vector2f(x,y);
  }
  return returnVal;
}

//helper function to find the squared distance between 2 points
float LogicSystem::squareDist(sf::Vector2f a, sf::Vector2f b){
  return (a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}

//calculates the angle between 2, from 0-360 degrees
float LogicSystem::calculateAngle(sf::Vector2f a, sf::Vector2f b){
  float dy = a.y - b.y;
  float dx = a.x - b.x;
  return atan2(dy, dx) * 180 / PI + 180;
}

//used to sort the anglePoints
bool compareAnglePoints(const anglePoint &lhs, const anglePoint &rhs)
{
    return lhs.angle < rhs.angle;
}



//gets all of the visio blocking points and sorts them by angle from the entity.
//So when you sweep from the entity starting on the right and going clockwise, the order at which
//you would hit the points is the order of the list
std::list<anglePoint>* LogicSystem::sortPointsByAngle(Entity *e){
  VisionComponent *vc = (VisionComponent*)e->getComponent(VISION);
  std::list<anglePoint>* result = new std::list<anglePoint>();

  bool needZeroAnglePoint = false;

  //add starting angle point
  anglePoint ap;
  ap.angle = vc->getDirection() - vc->getConeAngle()/2;
  if(ap.angle < 0){
    ap.angle += 360;
    needZeroAnglePoint = true;
  }
  sf::Vector2f infPoint = sf::Vector2f(e->getXY().x + vc->getLength()*cos(ap.angle*PI/180), e->getXY().y + vc->getLength()*sin(ap.angle*PI/180));
  sf::Vector2f origPoint = infPoint;
  infPoint = this->interSectLineAndRects(e->getXY(), infPoint, BVISION);
  if(infPoint == origPoint){
    ap.collision = false;
  }
  ap.point = infPoint;
  result->push_back(ap);
  if(ap.collision){
    this->addAnglePointsMidWall(e,  result,  ap.point, false); //you don't know if it is left or right. Just doing both works
    this->addAnglePointsMidWall(e,  result,  ap.point, true);
  }
  //add ending angle point
  ap.angle = vc->getDirection() + vc->getConeAngle()/2;
  if(ap.angle > 360){
    ap.angle -= 360;
    needZeroAnglePoint = true;
  }
  infPoint = sf::Vector2f(e->getXY().x + vc->getLength()*cos(ap.angle*PI/180), e->getXY().y + vc->getLength()*sin(ap.angle*PI/180));
  origPoint = infPoint;
  infPoint = this->interSectLineAndRects(e->getXY(), infPoint, BVISION);
  if(infPoint == origPoint){
    ap.collision = false;
  }else{
    ap.collision = true;
  }
  ap.point = infPoint;
  result->push_back(ap);
  if(ap.collision){
    this->addAnglePointsMidWall(e,  result,  ap.point, false);  //you don't know if it is horizontal or vertical. Just doing both works
    this->addAnglePointsMidWall(e,  result,  ap.point, true);
  }

  if(needZeroAnglePoint){
    ap.angle = 0;
    infPoint = sf::Vector2f(e->getXY().x + vc->getLength(), e->getXY().y);
    origPoint = infPoint;
    infPoint = this->interSectLineAndRects(e->getXY(), infPoint, BVISION);
    if(infPoint == origPoint){
      ap.collision = false;
    }else{
      ap.collision = true;
    }
    ap.point = infPoint;
    result->push_back(ap);
  }


  //add in initial angle point


  //grab all of the visionBlocking Points
  std::list<Entity>* eList = manager->getEntityList();
  std::list<Entity>::iterator iterator;
  for (iterator = eList->begin(); iterator != eList->end(); ++iterator) {
    if(iterator->hasComponent(BVISION)){
      BlockVisionComponent *bc = (BlockVisionComponent*)iterator->getComponent(BVISION);
      this->addAnglePoints(e, result,  bc->getTopLeft(), true, true); // top left
      this->addAnglePoints(e, result,  bc->getTopRight(), true, false); //top right
      this->addAnglePoints(e, result,  bc->getBottomLeft(), false, true); //bottom left
      this->addAnglePoints(e, result,  bc->getBottomRight(), false, false); //bottom right
    }
  }
  //sort the points based on their angle
  result->sort(&compareAnglePoints);

  return result;
}




void LogicSystem::addAnglePoints(Entity *e, std::list<anglePoint>* result,  sf::Vector2f v, bool cornerTop, bool cornerLeft){
  VisionComponent *vc = (VisionComponent*)e->getComponent(VISION);
  if(this->squareDist(e->getXY(), v) > vc->getLength()*vc->getLength()){
    return;
  }


  anglePoint ap;
  ap.point = v;
  bool top = e->getXY().y < ap.point.y;
  bool left = e->getXY().x <ap.point.x;
  bool bottom = !top;
  bool right = !left;

  //ray is coming from the other side of the square, so it won't be visible.
  if((cornerTop == bottom && cornerLeft == right)){
    return;
  }


   ap.angle = calculateAngle(e->getXY(), ap.point);

    bool over360 = false;
    float lowAngle = vc->getDirection() - vc->getConeAngle()/2;
    float highAngle = vc->getDirection() + vc->getConeAngle()/2;
    if(highAngle > 360){
      over360 = true;
      highAngle -= 360;
    }else if(lowAngle < 0){
      over360 = true;
      lowAngle+= 360;
    }
    if( !over360 && (ap.angle < lowAngle || ap.angle > highAngle)){
      return;
    }else if (over360 && (ap.angle > highAngle && ap.angle < lowAngle)){
      return;
    }

  //depending on which corner of the box that the line hits, we need to either
  //send an extra ray at a slightly higher or lower angle so that we have a point
  //exactly on the corner as well as one passing just past the corner to make the
  //vision cone move more smoothly
  if(cornerTop && cornerLeft){
    //top left set
    if(top && right){
      ap.after = true;
    }else if(bottom && left){
      ap.before = true;
    }
  }else if(cornerTop && !cornerLeft){
    //top right set
    if(bottom && right){
      ap.after = true;
    }else if(top && left){
      ap.before = true;
    }
  }else if(!cornerTop && cornerLeft){
    //bottom left set
    if(top && left){
      ap.after = true;
    }else if(bottom && right){
      ap.before = true;
    }
  }else if(!cornerTop && !cornerLeft){
    //bottom right set
    if(bottom && left){
      ap.after = true;
    }else if(top && right){
      ap.before = true;
    }
  }
  result->push_back(ap);


  //if the extra ray is needed, make it here
  sf::Vector2f infPoint;
  if(ap.before){
    ap.angle -= 0.01;
  }else if(ap.after){
    ap.angle+=0.01;
  }else{
    this->addAnglePointsMidWall(e, result, v,  true);
    this->addAnglePointsMidWall(e, result, v,  false);
    return;
  }
  infPoint = sf::Vector2f(e->getXY().x + vc->getLength()*cos(ap.angle*PI/180), e->getXY().y + vc->getLength()*sin(ap.angle*PI/180));
  sf::Vector2f origPoint = infPoint;
  infPoint = this->interSectLineAndRects(e->getXY(), infPoint, BVISION);
  if(infPoint == origPoint){
    ap.collision = false;
  }
  ap.point = infPoint;
  result->push_back(ap);
}

void LogicSystem::addAnglePointsMidWall(Entity *e, std::list<anglePoint>* result,  sf::Vector2f v, bool horizontal){
  VisionComponent* vc = (VisionComponent*)e->getComponent(VISION);


  bool comingFromTop = e->getXY().y < v.y;
  bool comingFromLeft = e->getXY().x < v.x;

  // std::cout << cornerTop << "  " << comingFromTop << std::endl;
  // std::cout << cornerLeft << "  " << comingFromLeft << std::endl << std::endl;

  //find the 2 connecting points
  // (cornerLeft*2-1) gives 1 for true, -1 for false
  sf::Vector2f point;
  if(horizontal){
    point = sf::Vector2f(v.x + (comingFromLeft*2-1)*50, v.y);
  }else{
    point = sf::Vector2f(v.x , v.y+ (comingFromTop*2-1)*50);
  }


  //if the connecting point isn't in the range, we need a point on the segment
  if(horizontal){
    if(this->squareDist(e->getXY(), point) > vc->getLength()*vc->getLength()){
      //use pythagorus
      float triY = e->getXY().y - point.y;
      float distAlongLine = sqrt((vc->getLength()*vc->getLength() - triY*triY));
      anglePoint ap;
      int pos = 1;
      if(e->getXY().x > point.x){
        pos = -1;
      }
      ap.point = sf::Vector2f(e->getXY().x + pos*distAlongLine, point.y);
      ap.angle = calculateAngle(e->getXY(), ap.point);

      if(comingFromTop){
        if(comingFromLeft){
          ap.before = true;
        }else{
          ap.after = true;
        }
      }else{
        if(comingFromLeft){
          ap.after = true;
        }else{
          ap.before = true;
        }
      }
      result->push_back(ap);
      if(ap.before || ap.after){

        sf::Vector2f infPoint;
        if(ap.before){
          ap.angle -= 0.01;
        }else if(ap.after){
          ap.angle+=0.01;
        }
        infPoint = sf::Vector2f(e->getXY().x + vc->getLength()*cos(ap.angle*PI/180), e->getXY().y + vc->getLength()*sin(ap.angle*PI/180));
        sf::Vector2f origPoint = infPoint;
        infPoint = this->interSectLineAndRects(e->getXY(), infPoint, BVISION);
        if(infPoint == origPoint){
          ap.collision = false;
        }
        ap.point = infPoint;
        result->push_back(ap);
      }
    }
  }else{
    if(this->squareDist(e->getXY(), point) > vc->getLength()*vc->getLength()){
      if(print)std::cout << "test\n";
      //use pythagorus
      float triX = e->getXY().x - point.x;
      float distAlongLine = sqrt((vc->getLength()*vc->getLength() - triX*triX));
      anglePoint ap;
      int pos = 1;
      if(e->getXY().y > point.x){
        pos = -1;
      }
      ap.point = sf::Vector2f(point.x, e->getXY().y + pos*distAlongLine);
      ap.angle = calculateAngle(e->getXY(), ap.point);
      if(comingFromLeft){
        if(comingFromTop){
          ap.after = true;
        }else{
          ap.before = true;
        }
      }else{
        if(comingFromTop){
          ap.before = true;
        }else{
          ap.after = true;
        }
      }
      result->push_back(ap);
      if(ap.before || ap.after){

        sf::Vector2f infPoint;
        if(ap.before){
          ap.angle -= 0.01;
        }else if(ap.after){
          ap.angle+=0.01;
        }
        infPoint = sf::Vector2f(e->getXY().x + vc->getLength()*cos(ap.angle*PI/180), e->getXY().y + vc->getLength()*sin(ap.angle*PI/180));
        sf::Vector2f origPoint = infPoint;
        infPoint = this->interSectLineAndRects(e->getXY(), infPoint, BVISION);
        if(infPoint == origPoint){
          ap.collision = false;
        }
        ap.point = infPoint;
        result->push_back(ap);
      }
    }
  }
}

void LogicSystem::moveEnemies(Entity *e) {
  MoveableComponent *mc = (MoveableComponent*)e->getComponent(MOVEABLE);
  std::cout << (mc->getMaxYPos());
  std::cout << (mc->getMinYPos());
  std::cout << (e->getXY().y) << "\n";
  if (e->getXY().x <= mc->getMinXPos() && e->getXY().y <= mc->getMinYPos()) {
    mc->setDirection(mc->getDirection() + 180);
  } else if (e->getXY().x >= mc->getMaxXPos() && e->getXY().y >= mc->getMaxYPos()) {
    mc->setDirection(mc->getDirection() + 180);
  }
}
