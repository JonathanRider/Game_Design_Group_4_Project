#include "collisionDetection.h"
#include <cmath>
namespace{
  int pointInLine(sf::Vector2f p, sf::Vector2f l1, sf::Vector2f l2) {
    //the line is made by l1 & l2. It is the programmer's responsibility to make sure l1 & l2 are not the same.
    //return 0 if p is on the line
    //For a specific line, if two points are on the same side, the return values should be the same (either 1 or -1)

    if (l1.x == l2.x) { //vertical line
        if (p.x < l1.x)
          return -1;
        else if (p.x > l1.x )
          return 1;
        else
          return 0; //the point is on the line
    }

    if (l1.y == l2.y) { //horizontal line
        if (p.y < l1.y)
          return -1;
        else if (p.y > l1.y )
          return 1;
        else
          return 0; //the point is on the line
    }

    //use the formula to get the line: y=(y2-y1)(x-x1)/(x2-x1)+y1
    float y = (l2.y - l1.y)*(p.x - l1.x) / (l2.x - l1.x ) + l1.y;
    if (p.y < y )
      return -1;
    else if (p.y > y)
      return 1;
    else
      return 0; //the point is in the line
  }

  bool twoLineParallel(sf::Vector2f l1, sf::Vector2f l2, sf::Vector2f s1, sf::Vector2f s2) {
    //return true if l & s are parallel
    //Assume the two lines are different
    if (l1.x == l2.x) { //vertical line
      if (s1.x == s2.x )
        return true;
      else
        return false;
    }
    if ( (l2.y-l1.y)/(l2.x-l1.x) == (s2.y-s1.y)/(s2.x-s1.x) )
      return true;
    else
      return false;
  }

  sf::Vector2f twoLineIntersection(sf::Vector2f l1, sf::Vector2f l2, sf::Vector2f s1, sf::Vector2f s2) {
    //return the intersection point of the two lines l & s
    //you need to make sure the two lines are not parallel
    sf::Vector2f intersection;

    if (twoLineParallel(l1,l2,s1,s2)) {
      intersection.x = intersection.y =0;
      return intersection;
    }

    if (l1.x == l2.x) { //vertical line
      intersection.x = l1.x;
      intersection.y = (s2.y-s1.y)*(intersection.x - s1.x)/(s2.x - s1.x) + s1.y;
      return intersection;
    }
    if (s1.x == s2.x) {//vertical line
      intersection.x = s1.x;
      intersection.y = (l2.y-l1.y)*(intersection.x - l1.x)/(l2.x - l1.x) + l1.y;
      return intersection;
    }

    intersection.x = ((s2.x - s1.x)*(l2.y-l1.y)*l1.x - (l2.x-l1.x)*(s2.y-s1.y)*s1.x + (s1.y-l1.y)*(l2.x-l1.x)*(s2.x-s1.x))\
      /( (s2.x-s1.x)*(l2.y-l1.y) - (l2.x-l1.x)*(s2.y-s1.y));
    intersection.y = (l2.y-l1.y)*(intersection.x - l1.x)/(l2.x - l1.x) + l1.y;
    return intersection;
  }

}

namespace collision {
  bool lineSegInTriangle(sf::Vector2f t1, sf::Vector2f t2, sf::Vector2f t3, sf::Vector2f l1, sf::Vector2f l2) {
    //the triangle is made by t1, t2 & t2; the line segment is made by l1 & l2
    //return true if the line segment lies or partially lies in the triangle
    int v1 = pointInLine(t1, l1, l2);
    int v2 = pointInLine(t2, l1, l2);
    int v3 = pointInLine(t3, l1, l2);
    sf::Vector2f inter1, inter2;
    bool isIntersectionSet = false;
    if (v1 == 0) {
      if (v2 == 0) {
        inter1 = t1;
        inter2 = t2;
        isIntersectionSet = true;
      } else if (v3 == 0){
        inter1 = t1;
        inter2 = t3;
        isIntersectionSet = true;
      } else{
        v1 = v2;
      }
    }

    if (v2 == 0) {
      if (v3 == 0){
        inter1 = t2;
        inter2 = t3;
        isIntersectionSet = true;
      } else{
        v2 = v1;
      }
    }

    if (v3 == 0) {
      v3 = v1;
    }


    if ( isIntersectionSet == false && v1 * v2 == -1 && v2 * v3 == 1 ) {
      inter1 = twoLineIntersection(t1, t2, l1, l2);
      inter2 = twoLineIntersection(t1, t3, l1, l2);
      isIntersectionSet = true;
    }
    if ( isIntersectionSet == false && v2 * v1 == -1 && v1 * v3 == 1 ) {
      inter1 = twoLineIntersection(t2, t1, l1, l2);
      inter2 = twoLineIntersection(t2, t3, l1, l2);
      isIntersectionSet = true;
    }
    if ( isIntersectionSet == false && v3 * v1 == -1 && v1 * v2 == 1 ) {
      inter1 = twoLineIntersection(t3, t1, l1, l2);
      inter2 = twoLineIntersection(t3, t2, l1, l2);
      isIntersectionSet = true;

    }

    if (isIntersectionSet) {
      if (l1.x == l2.x) {
        if ( ( (l1.y < inter1.y && l2.y < inter1.y) && (l1.y < inter2.y && l2.y < inter2.y ) )
          || ( (l1.y > inter1.y && l2.y > inter1.y) && (l1.y > inter2.y && l2.y > inter2.y ) ) )
          return false;
        else
          return true;
      }
      else {

        if ( ( (l1.x < inter1.x && l2.x < inter1.x) && (l1.x < inter2.x && l2.x < inter2.x ) )
          || ( (l1.x > inter1.x && l2.x > inter1.x) && (l1.x > inter2.x && l2.x > inter2.x ) ) )
          return false;
        else
          return true;
      }
    }
    else
      return false;
  }

  bool triIntersectRect(sf::Vector2f t1, sf::Vector2f t2, sf::Vector2f t3, sf::FloatRect rect) {
    //the triangle is made by t1, t2 & t2.
    //return true if the triangle & the rectangle intersect
    if ( rect.contains(t1) || rect.contains(t2) || rect.contains(t3) )
      return true;
    if (lineSegInTriangle(t1,t2,t3,sf::Vector2f(rect.left, rect.top), sf::Vector2f(rect.left+rect.width, rect.top))
      || lineSegInTriangle(t1,t2,t3,sf::Vector2f(rect.left+rect.width, rect.top), sf::Vector2f(rect.left+rect.width, rect.top+rect.height))
      || lineSegInTriangle(t1,t2,t3,sf::Vector2f(rect.left+rect.width, rect.top+rect.height), sf::Vector2f(rect.left, rect.top+rect.height))
      || lineSegInTriangle(t1,t2,t3,sf::Vector2f(rect.left, rect.top+rect.height), sf::Vector2f(rect.left, rect.top) ) )
        return true;
    return false;
  }
}
