#ifndef _BLOCK_SIGHT_H_
#define _BLOCK_SIGHT_H_

#include "components/component.h"
#include "SFML/Graphics.hpp"

class BlockVisionComponent : public Component
{
public:
  BlockVisionComponent(sf::Vector2f xy, float height, float width);
  ~BlockVisionComponent();

  sf::VertexArray getTop(){return top;}
  sf::VertexArray getBottom(){return bottom;}
  sf::VertexArray getRight(){return right;}
  sf::VertexArray getLeft() {return left;}

  sf::Vector2f getTopLeft(){return topLeft;}
  sf::Vector2f getTopRight(){return topRight;}
  sf::Vector2f getBottomLeft(){return bottomLeft;}
  sf::Vector2f getBottomRight(){return bottomRight;}

  void setTopLeft(sf::Vector2f tl);
  void setTopRight(sf::Vector2f tr);
  void setBottomLeft(sf::Vector2f bl);
  void setBottomRight(sf::Vector2f br);

  void moveTo(sf::Vector2f xy);


private:
  sf::Vector2f topLeft;
  sf::Vector2f topRight;
  sf::Vector2f bottomLeft;
  sf::Vector2f bottomRight;

  sf::VertexArray top;
  sf::VertexArray left;
  sf::VertexArray right;
  sf::VertexArray bottom;

  float height;
  float width;


};


#endif
