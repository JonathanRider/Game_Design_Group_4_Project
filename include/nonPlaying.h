#ifndef _NON_PLAYING_H_
#define _NON_PLAYING_H_
#include "global.h"
#include <SFML/Graphics.hpp>
#include <map>

class Menu {
public:
  Menu(){}
  virtual ~Menu(){}
  virtual void receiveInput(constants::Input input, void *extra_data) = 0;
  virtual void draw(sf::RenderWindow &w) = 0;
};

class LevelMenu: public Menu {
public:
  LevelMenu();
  ~LevelMenu();
  void receiveInput(constants::Input input, void *extra_data);
  void draw(sf::RenderWindow &w);
private:
  void drawCell(sf::RenderWindow &w, int row_position, int column_position);
  void calculateInterval(float window_width, float window_height);
  int getCurrentLevel();
  std::map<int, std::string> level_file_map;
  int position_row, position_column; //start from 0
  int num_row, num_column;
  float cell_width, cell_height;
  float margin_left, margin_right, margin_top, margin_down;
  float interval_horizontal, interval_vertical;
};

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
  LevelMenu levelMenu;
};

#endif
