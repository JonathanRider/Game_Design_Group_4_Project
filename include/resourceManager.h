#ifndef _RESOURCE_MANAGER_H_
#define _RESOURCE_MANAGER_H_

#include <map>
#include <string>
#include <SFML/Graphics.hpp>
class ResourceManager {
//This class is used to centrally provide texture and font to avoid multiple loading.
public:
  ResourceManager();
  ~ResourceManager();

  sf::Texture *getTexture(std::string &path);
  sf::Font *getFont(std::string &path);
  sf::Font *getFont(const char *path);

private:
  std::map<std::string, sf::Texture *> texture_map;
  std::map<std::string, sf::Font *> font_map;
};

#endif
