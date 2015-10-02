#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "graphicsComponent.h"
#include <map>
#include <SFML/Graphics.hpp>
class entity
{
public:
  entity(int id);
  ~entity(){}

  void getId();
  bool hasComponent(int c);
  void addComponent(component c);
  void removeComponent(int c); //eventually enum
  void removeAllComponents();
  component* getComponent(int type);

  void setXY(sf::Vector2f xy);
  sf::Vector2f getXY(){return xy;}

private:
  std::map<int, component> componentMap;
  int id;
  sf::Vector2f xy;

};

#endif
