#include "nonPlaying.h"
#include "typeConversion.h"
#include <iostream>
#include <string>

StoryMenu::StoryMenu(){}
StoryMenu::~StoryMenu(){}
void StoryMenu::receiveInput(constants::Input input, int &state, void *extra_data){

  switch (input) {
    case constants::INPUT_CONFIRM:
    {
      bool *b_instory= (bool *) extra_data;
      global()->gameEngine.entityManager->clearAll();
      global()->gameEngine.levelCreator->loadAndCreateLevel(level_file);
      global()->gameEngine.gameState = constants::PLAYING;
      *b_instory = false;
    }
      break;
    default:
      break;
  }
}
void StoryMenu::draw(sf::RenderWindow &w){
  sf::Sprite sprite;
  sf::Texture *p_texture;
  p_texture= global()->gameEngine.resourceManager->getTexture("resources/graphics/image/Win.png");
  sprite.setTexture(*p_texture);
  w.draw(sprite);
}

LevelMenu::LevelMenu():position_row(0),position_column(0), num_row(3), num_column(3),
cell_width(100), cell_height(80),
margin_left(100), margin_right(100), margin_top(50), margin_down(50),
b_instory(false){
  level_file_map[1] = std::string("resources/levels/level_01.xml"); //this is level 1
  level_file_map[2] = std::string("resources/levels/level_02.xml");
  level_file_map[3] = std::string("resources/levels/level_03.xml");
  level_file_map[4] = std::string("resources/levels/level_04.xml");
  level_file_map[5] = std::string("resources/levels/level_05.xml");
  level_file_map[6] = std::string("resources/levels/level_06.xml");
  level_file_map[7] = std::string("resources/levels/level_07.xml");
  level_file_map[8] = std::string("resources/levels/level_08.xml");
  level_file_map[9] = std::string("resources/levels/level_09.xml");
}
LevelMenu::~LevelMenu(){}
void LevelMenu::receiveInput(constants::Input input, int &state, void *extra_data){
  if (b_instory){
    storyMenu.receiveInput(input, state, &b_instory);
    return;
  }
  switch (input) {
    case constants::INPUT_UP:
      position_row--;
      break;
    case constants::INPUT_DOWN:
      position_row++;
      break;
    case constants::INPUT_LEFT:
      position_column--;
      break;
    case constants::INPUT_RIGHT:
      position_column++;
      break;
    case constants::INPUT_ESC:
      state = NonPlaying::MAINMENU;
      break;
    case constants::INPUT_CONFIRM:
      if (level_file_map.find(getCurrentLevel()) != level_file_map.end() ){
        storyMenu.setLevelFile(level_file_map[getCurrentLevel()]);
        b_instory = true;
      }
      break;
    default:
      break;
  }
  if (position_row < 0)
    position_row = 0;
  if (position_row >= num_row)
    position_row = num_row - 1;
  if (position_column < 0)
    position_column = 0;
  if (position_column >= num_column)
    position_column = num_column - 1;
}
void LevelMenu::draw(sf::RenderWindow &w){
  if (b_instory){
    storyMenu.draw(w);
    return;
  }
  //calculateInterval(w.getSize().x, w.getSize().y);
  calculateInterval(800, 600);
  w.clear(sf::Color(0, 0, 0, 255));

  for(int i=0; i < num_row; i++)
    for(int j=0; j < num_column; j++){
      drawCell(w,i, j);
    }
}
void LevelMenu::drawCell(sf::RenderWindow &w, int row_position, int column_position){
  float x, y;
  //calculate the position
  x = margin_left + (cell_width + interval_horizontal) * column_position;
  y = margin_top + (cell_height + interval_vertical) * row_position;

  //get level string
  std::string level_string = "Level " + typeconvert::int2string(row_position * num_column + column_position + 1 );

  sf::RectangleShape box;
  box.setSize(sf::Vector2f(cell_width, cell_height));
  box.setOutlineColor(sf::Color::Red);
  box.setOutlineThickness(5);
  box.setPosition(x,y);
  if (position_row == row_position && position_column == column_position){
    box.setFillColor(sf::Color(255,255,255,255));
  }
  else {
    box.setFillColor(sf::Color(255,255,255,0));
  }

  sf::Text text;
  text.setFont(*(global()->gameEngine.resourceManager->getFont("resources/font/6809 chargen.ttf")));
  text.setCharacterSize(24);
  text.setColor(sf::Color::Red);
  text.setPosition(x,y);
  text.setString(level_string);

  w.draw(box);
  w.draw(text);
}
void LevelMenu::calculateInterval(float window_width, float window_height){
  interval_horizontal = (window_width - margin_left - margin_right - cell_width * num_column)/(num_column - 1);
  if (interval_horizontal < 0)
    interval_horizontal = 0;
  interval_vertical = (window_height - margin_top - margin_down -cell_height * num_row)/(num_row - 1);
  if (interval_vertical < 0)
    interval_vertical = 0;
}
int LevelMenu::getCurrentLevel(){
  return position_row * num_column + position_column + 1;
}

MainMenu::MainMenu():current_index(0){}
MainMenu::~MainMenu(){}
void MainMenu::receiveInput(constants::Input input, int &state, void *extra_data){
  switch (input) {
    case constants::INPUT_UP:
      current_index--;
      break;
    case constants::INPUT_DOWN:
      current_index++;
      break;
    case constants::INPUT_CONFIRM:
      if (current_index == 0) { //levelMenu
        state = NonPlaying::LEVELMENU;
      }
      else if (current_index == 1) { //optionsMenu
        //state = NonPlaying::OPTIONSMENU
      }
      break;
    default:
      break;
  }
  if (current_index < 0)
    current_index = 0;
  if (current_index > 1)
    current_index = 1;
}
void MainMenu::draw(sf::RenderWindow &w){
  sf::Sprite sprite;
  sf::Texture *p_texture;
  if (current_index == 0) {
    p_texture= global()->gameEngine.resourceManager->getTexture("resources/graphics/image/MainMenu0.png");
  }
  else {
    p_texture = global()->gameEngine.resourceManager->getTexture("resources/graphics/image/MainMenu1.png");
  }
  sprite.setTexture(*p_texture);
  w.draw(sprite);
}

OptionsMenu::OptionsMenu(){}
OptionsMenu::~OptionsMenu(){}
void OptionsMenu::receiveInput(constants::Input input, int &state, void *extra_data){}
void OptionsMenu::draw(sf::RenderWindow &w){}

TerminalMenu::TerminalMenu():b_win(false){}
TerminalMenu::~TerminalMenu(){}
void TerminalMenu::receiveInput(constants::Input input, int &state, void *extra_data){
  switch (input) {
    case constants::INPUT_CONFIRM:
      state = NonPlaying::LEVELMENU;
      break;
    default:
      break;
  }
}
void TerminalMenu::draw(sf::RenderWindow &w){
  sf::Sprite sprite;
  sf::Texture *p_texture;
  if (b_win) {
    p_texture= global()->gameEngine.resourceManager->getTexture("resources/graphics/image/Win.png");
  }
  else {
    p_texture = global()->gameEngine.resourceManager->getTexture("resources/graphics/image/GameOver.png");
  }
  sprite.setTexture(*p_texture);
  w.draw(sprite);
}


NonPlaying::NonPlaying():internal_state(MAINMENU){}
NonPlaying::~NonPlaying(){}

void NonPlaying::receiveInput(constants::Input input, void *extra_data){
  if (input == constants::INPUT_WIN){
    terminalMenu.setWin(true);
    internal_state = TERMINALMENU;
  } else if (input == constants::INPUT_LOSE){
    terminalMenu.setWin(false);
    internal_state = TERMINALMENU;
  }
  else{
    switch(internal_state) {
      case MAINMENU:
        mainMenu.receiveInput(input, (int &)internal_state);
        return;
      case LEVELMENU:
        levelMenu.receiveInput(input, (int &)internal_state);
        return;
      case OPTIONSMENU:
        optionsMenu.receiveInput(input,(int &)internal_state);
        return;
      case TERMINALMENU:
        terminalMenu.receiveInput(input, (int &)internal_state);
        return;
      default:
        return;
    }
  }
}

void NonPlaying::draw(sf::RenderWindow &w){

  if (internal_state == MAINMENU) {
    w.setView(w.getDefaultView());
    mainMenu.draw(w);
  } else if (internal_state == TERMINALMENU  ) {
    w.setView(w.getDefaultView()); //reset view
    terminalMenu.draw(w);
  } else if (internal_state == LEVELMENU) {
    w.setView(w.getDefaultView()); //reset view
    levelMenu.draw(w);
  }
}
