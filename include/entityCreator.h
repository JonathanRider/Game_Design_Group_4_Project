#ifndef _ENTITY_CREATOR_H_
#define _ENTITY_CREATOR_H_

#include "allComponents.h"
#include "entityManager.h"
#include "entity.h"
#include "constants.h"
#include "SFML/Graphics.hpp"
#include <vector>
#include <map>

class EntityCreator
{
public:
  EntityCreator(EntityManager *em);
  ~EntityCreator();

  void create(constants::EntityType type, sf::Vector2f xy, std::string sprite_file_name = "");

  void createGrenade(sf::Vector2f xy, float direction, float velocity, float drag, std::string sprite_file_name = "");
  void createPlayer(sf::Vector2f xy, std::string sprite_file_name = "");
  void createWall(sf::Vector2f xy, float width, float height, std::string sprite_file_name = "");
  void createBox(sf::Vector2f xy, std::string sprite_file_name = "");
  void createMovingEnemy(sf::Vector2f xy, std::string sprite_file_name = "");
  void createStaticEnemy(sf::Vector2f xy, std::string sprite_file_name = "");
  void createFinish(sf::Vector2f xy, std::string sprite_file_name = "");
  void createSmokeScreen(sf::Vector2f xy, std::string sprite_file_name = "");
  void createTrap(sf::Vector2f xy, bool isVisible = true, std::string sprite_file_name = "");
  void createInventory(sf::Vector2f xy, std::map<std::string, std::string> &item_list);
private:


  class TextureManager {
  public:
    void addTexture(std::string &file_name, int index = -1);
    void addTexture(const char *file_name, int index = -1);
    sf::Texture *getTexture(std::string &file_name);
    sf::Texture *getTexture(int index);
  private:
    std::map<int, std::string> index_to_name;
  };
  enum TextureIndex {WALL, PLAYER, ENEMY, BULLET, GRENADE, EXIT, BOX, SMOKE, TRAP, NUM_OF_TEXTURES};
  TextureManager textureManager;
  EntityManager *em;

};

#endif
