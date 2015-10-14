#ifndef _VISION_COMPONENT_H_
#define _VISION_COMPONENT_H_

#include "components/component.h"
#include "SFML/Graphics.hpp"


class VisionComponent : public Component
{
public:
  VisionComponent(sf::Vector2f location, float l, float dir, float a);
  ~VisionComponent();

  void setLength(float l){length = l;}
  float getLength(){return length;}
  void setDirection(float dir){direction = dir;}
  float getDirection(){return direction;}
  void setConeAngle(float a){coneAngle = a;}
  float getConeAngle(){return coneAngle;}

  float getVisionResolution(){return visionResolution;}

  sf::VertexArray* getTriangles(){return triFan;}






private:
  sf::Vector2f xy;
  float length;
  float direction;
  float coneAngle;
  float visionResolution;

  bool alert;
  sf::VertexArray* triFan;

};

#endif
