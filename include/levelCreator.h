#ifndef _LEVEL_CREATOR_H_
#define _LEVEL_CREATOR_H_

#include "entityManager.h"
#include "entityCreator.h"

#include <string>
#include <constants.h>
#include <SFML/Graphics.hpp>

class LevelCreator {
public:
  LevelCreator(EntityManager *m);
  ~LevelCreator();

  void loadAndCreateLevel(std::string &fileName);
private:

  EntityManager * manager;
  EntityCreator eCreator;
  float scale;
};



#endif
