#ifndef _ENTITY_CREATOR_H_
#define _ENTITY_CREATOR_H_

#include "allComponents.h"
#include "entityManager.h"
#include "entity.h"
#include "constants.h"
#include "SFML/Graphics.hpp"
#include <vector>

class EntityCreator
{
public:
  EntityCreator(EntityManager *em);
  ~EntityCreator();

  void create(constants::EntityType type, sf::Vector2f xy);

  void createGrenade(sf::Vector2f xy, float direction, float velocity, float drag);
  void createPlayer(sf::Vector2f xy);
  void createWall(sf::Vector2f xy, float width, float height);
  void createBox(sf::Vector2f xy);
  void createMovingEnemy(sf::Vector2f xy);
  void createStaticEnemy(sf::Vector2f xy);
  void createFinish(sf::Vector2f xy);
private:
  enum TextureIndex {WALL, PLAYER, ENEMY, BULLET, EXIT, BOX, NUM_OF_TEXTURES};//only for texture_table
  std::vector<sf::Texture *> texture_table;



  EntityManager *em;
};

#endif
