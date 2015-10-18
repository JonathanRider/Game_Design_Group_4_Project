#ifndef _COLLISION_DETECTION_H_
#define _COLLISION_DETECTION_H_
#include<SFML/Graphics.hpp>


namespace collision {
    bool lineSegInTriangle(sf::Vector2f t1, sf::Vector2f t2, sf::Vector2f t3, sf::Vector2f l1, sf::Vector2f l2);
    bool triIntersectRect(sf::Vector2f t1, sf::Vector2f t2, sf::Vector2f t3, sf::FloatRect rect);
}
#endif
