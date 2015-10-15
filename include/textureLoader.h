#ifndef _TEXTURE_LOADER_H_
#define _TEXTURE_LOADER_H_

#include <SFML\Graphics.hpp>
#include <map>
#include <string>
#include "constants.h"

enum TextureType {
	TEXTURE_TYPE_1, //We need to rename it again
	TEXTURE_TYPE_2,
};

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
