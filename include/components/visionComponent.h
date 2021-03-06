#ifndef _VISION_COMPONENT_H_
#define _VISION_COMPONENT_H_

#include "components/component.h"
#include "SFML/Graphics.hpp"


class VisionComponent : public Component
{
public:
  VisionComponent(sf::Vector2f location, float l, float dir, float a, float minRAngle = 0, float maxRAngle = 0);
  ~VisionComponent(){delete triFan;}

  void setLength(float l){length = l;}
  float getLength(){return length;}
  void setDirection(float dir){direction = dir;}
  float getDirection(){return direction;}
  void setConeAngle(float a){coneAngle = a;}
  float getConeAngle(){return coneAngle;}
  void setAlert(bool a){ alert = a;}
  bool getAlert(){ return alert; }
  float getVisionResolution(){return visionResolution;}

  void setMinRotateAngle(float a){minRotateAngle = a;}
  float getMinRotateAngle(){return minRotateAngle;}
  void setMaxRotateAngle(float a){maxRotateAngle = a;}
  float getMaxRotateAngle(){return maxRotateAngle;}
  int getRotateDirection(){return rotateDirection;}
  void setRotateDirection(int d){rotateDirection = d;}

  void rotate(float time);

  sf::VertexArray* getTriangles(){return triFan;}






private:
  sf::Vector2f xy;
  float length;
  float direction;
  float coneAngle;
  float visionResolution;

  float minRotateAngle;
  float maxRotateAngle;
  int rotateDirection;

  bool alert;
  sf::VertexArray* triFan;

};

#endif
