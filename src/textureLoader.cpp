#include "textureLoader.h"

sf::Texture* TextureLoader::getLevelTextures(TextureType type) {
  std::map<TextureType,sf::Texture*>::iterator it =  levelTextureMap.find(type);
  return (it->second); //return the value of the key-value pair
}

sf::Texture* TextureLoader::getPersistentTextures(TextureType type) {
  std::map<TextureType,sf::Texture*>::iterator it =  persistentTextureMap.find(type);
  return (it->second); //return the value of the key-value pair
}
