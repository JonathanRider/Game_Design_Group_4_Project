#ifndef _ENTITY_CREATOR_H_
#define _ENTITY_CREATOR_H_

#include "allComponents.h"
#include "entityManager.h"
#include "entity.h"
#include "constants.h"
#include "SFML/Graphics.hpp"

class EntityCreator
{
public:
  EntityCreator(EntityManager *em):em(em){}
  ~EntityCreator();

  void create(constants::EntityType type, sf::Vector2f xy, sf::Texture *texture);

  void createGrenade(sf::Vector2f xy, float direction, float velocity, float drag, sf::Texture *texture);
private:

  void createPlayer(sf::Vector2f xy, sf::Texture *texture);
  void createWall(sf::Vector2f xy,  sf::Texture *texture);
  void createMovingEnemy(sf::Vector2f xy, sf::Texture *texture);


  EntityManager *em;
};

#endif
