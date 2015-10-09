#ifndef _TEXTURE_LOADER_H_
#define _TEXTURE_LOADER_H_

#include <SFML\Graphics.hpp>
#include <map>
#include <string>
#include "constants.h"

class TextureLoader
{
public:
  TextureLoader(){}
  ~TextureLoader();

  void loadPersistentTextures(std::string fileName, TextureType type);
  void loadLevelTextures(std::string fileName, TextureType type);
  sf::Texture* getLevelTextures(TextureType type);
  sf::Texture* getPersistentTextures(TextureType type);



private:
  std::map<TextureType, sf::Texture*> levelTextureMap;
  std::map<TextureType, sf::Texture*> persistentTextureMap;

};

#endif
