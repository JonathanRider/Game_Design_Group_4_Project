#include "resourceManager.h"

ResourceManager::ResourceManager(){}

ResourceManager::~ResourceManager(){
  for (std::map<std::string, sf::Texture *>::const_iterator it = texture_map.begin(); it != texture_map.end(); it++) {
    delete it->second;
  }
  for (std::map<std::string, sf::Font *>::const_iterator it = font_map.begin(); it != font_map.end(); it++) {
    delete it->second;
  }
}

sf::Texture *ResourceManager::getTexture(std::string &path){
  std::map<std::string, sf::Texture *>::const_iterator it;
  if ( (it = texture_map.find(path)) == texture_map.end() ) { //not found
    sf::Texture *texture_tmp = new sf::Texture();
    texture_tmp->loadFromFile(path);
    texture_map.insert(std::map<std::string, sf::Texture *>::value_type(path, texture_tmp));
    return texture_tmp;
  }
  else {
    return it->second;
  }
}
sf::Texture *ResourceManager::getTexture(const char *path){
  std::string path_string = path;
  return getTexture(path_string);
}
sf::Font *ResourceManager::getFont(std::string &path){
  std::map<std::string, sf::Font *>::const_iterator it;
  if ( (it = font_map.find(path)) == font_map.end() ) { //not found
    sf::Font *font_tmp = new sf::Font();
    font_tmp->loadFromFile(path);
    font_map.insert(std::map<std::string, sf::Font *>::value_type(path, font_tmp));
    return font_tmp;
  }
  else {
    return it->second;
  }
}

sf::Font *ResourceManager::getFont(const char *path){
  std::string path_string = path;
  return getFont(path_string);
}
