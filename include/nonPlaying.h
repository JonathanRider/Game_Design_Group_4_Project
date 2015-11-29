#ifndef _NON_PLAYING_H_
#define _NON_PLAYING_H_
#include "global.h"
#include <SFML/Graphics.hpp>

class NonPlaying {
  //This class handles everything when the game is not in playing state;
public:
  NonPlaying();
  ~NonPlaying();

  void receiveInput(constants::Input input, void *extra_data);
  void draw(sf::RenderWindow &w);
private:
  std::vector<sf::Texture*> menuTextures; //should be moved later
  std::vector<sf::Sprite*> mainMenuSprites;
  std::vector<sf::Sprite*> levelMenuSprites;
  std::vector<std::vector<sf::Sprite*> > textSprites;
  sf::Sprite* gameOverSprite;
  sf::Sprite* winSprite;
};

#endif
