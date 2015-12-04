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
  void setLevel(int l) {level = l;}
  void setBonus(bool t){bonus = t;}
  bool getBonus(){return bonus;}
private:
  std::string level_file;
  int level;
  bool bonus;
  std::map<int,std::string> story_board_map;
};
class LevelMenu: public Menu {
public:
  LevelMenu();
  ~LevelMenu();
  void receiveInput(constants::Input input, int &state, void *extra_data = NULL);
  void draw(sf::RenderWindow &w);
  int getCurrentLevel();
protected:
  class Page{
  public:
    Page(int row, int col);
    ~Page();
    int move(const char *direction);
    void setBackgroundTexture(const char *texture_file);
    void setLevelDisplayString(int level, const char *str);//level from 1
    void setPageParameters(const char *name, float value);
    void draw(sf::RenderWindow &w);
    void drawCell(sf::RenderWindow &w, int row_position, int column_position, bool b_selected);
    void calculateInterval(float window_width, float window_height);
    int getCurrentLevel(){return selected_row * n_col + selected_col + 1;}
  private:
    sf::Sprite background_sprite;
    std::vector<std::string> level_display_list;
    int n_row, n_col, selected_row, selected_col;
    float cell_width, cell_height;
    float margin_left, margin_right, margin_top, margin_down;
    float interval_horizontal, interval_vertical;
    float text_x_offset, text_y_offset;
  };
  std::vector<Page *> page_list;

  StoryMenu storyMenu;
  bool b_instory;
  std::map<int, std::string> level_file_map;
  int current_page;
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

class InfoMenu: public Menu {
public:
  InfoMenu();
  ~InfoMenu();
  void receiveInput(constants::Input input, int &state, void *extra_data = NULL);
  void draw(sf::RenderWindow &w);

private:
  int current_index;
  bool inMenu;
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
  enum NonPlayingState {MAINMENU, LEVELMENU, TERMINALMENU, INFOMENU, CONTROLS, ENEMIES, ITEMS};
  NonPlayingState getState(){return internal_state;}
  void setState(NonPlayingState s){internal_state = s;}
private:
  NonPlayingState internal_state;
  LevelMenu levelMenu;
  InfoMenu infoMenu;
  MainMenu mainMenu;
  TerminalMenu terminalMenu;
};

#endif
