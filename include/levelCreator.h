#ifndef _LEVEL_CREATOR_H_
#define _LEVEL_CREATOR_H_

#include "entityManager.h"
#include "entityCreator.h"

#include <set>
#include <vector>
#include <string>
#include <constants.h>
#include <SFML/Graphics.hpp>




namespace levelCreator_internal { //it is only used in this file
  class WorldComponent {
  public:
    WorldComponent(EntityType i_t, float i_x, float i_y, std::set<int> *set_p = NULL)
      : type(i_t), x(i_x), y(i_y), property_set(set_p){}
    ~WorldComponent(){
      delete property_set;
    }
    EntityType type;
    float x, y;
    std::set<int> * property_set;
  };

}


class LevelCreator {
public:
  LevelCreator(EntityManager *m);
  ~LevelCreator();

  void loadLevelFile(std::string &fileName);
  void createLevel();
private:
  std::vector<levelCreator_internal::WorldComponent *> creation_list;
  sf::Texture *wallTex;
  sf::Texture *tex_player;
  sf::Texture *tex_enemy;

  EntityManager * manager;
  EntityCreator eCreator;
  float scale;

  void clearList();


};



#endif
