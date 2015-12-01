#ifndef _NON_PLAYING_H_
#define _NON_PLAYING_H_
#include "global.h"
#include <SFML/Graphics.hpp>
#include <map>



class Menu {
public:
  Menu(){}
  virtual ~Menu(){}
  virtual void receiveInput(constants::Input input, int &state, void *extra_data = NULL) = 0;
  virtual void draw(sf::RenderWindow &w) = 0;
};

class StoryMenu: public Menu {
public:
  StoryMenu();
  ~StoryMenu();
  void receiveInput(constants::Input input, int &state, void *extra_data = NULL);
  void draw(sf::RenderWindow &w);
  void setLevelFile(std::string &name){level_file = name;}
private:
  std::string level_file;
};
class LevelMenu: public Menu {
public:
  LevelMenu();
  ~LevelMenu();
  void receiveInput(constants::Input input, int &state, void *extra_data = NULL);
  void draw(sf::RenderWindow &w);
private:
  void drawCell(sf::RenderWindow &w, int row_position, int column_position);
  void calculateInterval(float window_width, float window_height);
  int getCurrentLevel();
  StoryMenu storyMenu;
  bool b_instory;
  std::map<int, std::string> level_file_map;
  int position_row, position_column; //start from 0
  int num_row, num_column;
  float cell_width, cell_height;
  float margin_left, margin_right, margin_top, margin_down;
  float interval_horizontal, interval_vertical;
};

class MainMenu: public Menu {
public:
  MainMenu();
  ~MainMenu();
  void receiveInput(constants::Input input, int &state, void *extra_data = NULL);
  void draw(sf::RenderWindow &w);
private:
  int current_index;
};

class OptionsMenu: public Menu {
public:
  OptionsMenu();
  ~OptionsMenu();
  void receiveInput(constants::Input input, int &state, void *extra_data = NULL);
  void draw(sf::RenderWindow &w);
};
class TerminalMenu: public Menu { //for win or lose
public:
  TerminalMenu();
  ~TerminalMenu();
  void receiveInput(constants::Input input, int &state, void *extra_data = NULL);
  void draw(sf::RenderWindow &w);
  bool isWin(){return b_win;}
  void setWin(bool b){b_win = b;}
private:
  bool b_win;
};



class NonPlaying {
  //This class handles everything when the game is not in playing state;
public:
  NonPlaying();
  ~NonPlaying();

  void receiveInput(constants::Input input, void *extra_data);
  void draw(sf::RenderWindow &w);
  enum NonPlayingState {MAINMENU, LEVELMENU, OPTIONSMENU, TERMINALMENU};
  NonPlayingState getState(){return internal_state;}
private:
  NonPlayingState internal_state;
  LevelMenu levelMenu;
  OptionsMenu optionsMenu;
  MainMenu mainMenu;
  TerminalMenu terminalMenu;
};

#endif
