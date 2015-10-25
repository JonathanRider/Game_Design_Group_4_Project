#ifndef _ENTITY_H_
#define _ENTITY_H_


#include "allComponents.h"
#include <map>
#include <SFML/Graphics.hpp>
class Entity
{
public:
  Entity(int id);
  ~Entity();

  int getID(){return id;}
  bool hasComponent(ComponentType type);
  void addComponent(Component* c);
  void removeComponent(ComponentType type); //eventually enum
  void removeAllComponents();
  Component* getComponent(ComponentType type);

  void setXY(sf::Vector2f Newxy);
  sf::Vector2f getXY(){return xy;}

private:
  std::map<ComponentType, Component*> componentMap;
  int id;
  sf::Vector2f xy;

};

#endif
