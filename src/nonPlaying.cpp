#include "nonPlaying.h"
#include "typeConversion.h"
#include <iostream>
#include <string>

StoryMenu::StoryMenu(){
  story_board_map[1] = "resources/graphics/image/level_01_story.png";
  story_board_map[2] = "resources/graphics/image/level_02_story.png";
  story_board_map[3] = "resources/graphics/image/level_03_story.png";
  story_board_map[4] = "resources/graphics/image/level_04_story.png";
  story_board_map[5] = "resources/graphics/image/level_05_story.png";
  story_board_map[6] = "resources/graphics/image/level_06_story.png";
  story_board_map[7] = "resources/graphics/image/level_07_story.png";
  story_board_map[8] = "resources/graphics/image/level_08_story.png";
  story_board_map[9] = "resources/graphics/image/level_09_story.png";
  story_board_map[10] = "resources/graphics/image/bonus/level_Lava_story.png";
  story_board_map[11] = "resources/graphics/image/bonus/level_sumo_story.png";
  story_board_map[12] = "resources/graphics/image/bonus/level_space_story.png";
  story_board_map[13] = "resources/graphics/image/bonus/level_Dino_story.png";
  story_board_map[14] = "resources/graphics/image/bonus/level_spiders_story.png";
  story_board_map[15] = "resources/graphics/image/bonus/level_bond_story.png";
}
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
  int actualLevel= level;
  if(getBonus()){
    actualLevel += 9;
  }
  p_texture= global()->gameEngine.resourceManager->getTexture(story_board_map[actualLevel]);
  sprite.setTexture(*p_texture);
  w.draw(sprite);
}
BonusLevelMenu::BonusLevelMenu():position_row(0),position_column(0), num_row(2), num_column(3),
cell_width(160), cell_height(160),
margin_left(110), margin_right(115), margin_top(56), margin_down(60),
b_instory(false){

  storyMenu.setBonus(true);
  level_file_map[1] = std::string("resources/levels/level_Lava.xml");
  level_file_map[2] = std::string("resources/levels/level_sumo.xml");
  level_file_map[3] = std::string("resources/levels/level_space.xml");
  level_file_map[4] = std::string("resources/levels/level_Dino.xml");
  level_file_map[5] = std::string("resources/levels/level_spiders.xml");
  level_file_map[6] = std::string("resources/levels/level_bond.xml");
}

void BonusLevelMenu::draw(sf::RenderWindow &w){
  if (b_instory){
    storyMenu.draw(w);
    return;
  }
  //calculateInterval(w.getSize().x, w.getSize().y);
  calculateInterval(800, 600);
  w.clear(sf::Color(0, 0, 0, 255));
  sf::Sprite background;
  //background.setTexture(*global()->gameEngine.resourceManager->getTexture("resources/graphics/image/LevelMenu.png"));
  w.draw(background);
  for(int i=0; i < num_row; i++)
    for(int j=0; j < num_column; j++){
      drawCell(w,i, j);
    }
}
void BonusLevelMenu::drawCell(sf::RenderWindow &w, int row_position, int column_position){
  float x, y;
  //calculate the position
  x = margin_left + (cell_width + interval_horizontal) * column_position;
  y = margin_top + (cell_height + interval_vertical) * row_position;

  //get level string
  int temp = row_position * num_column + column_position + 1;
  std::string level_string;
  switch(temp){
    case 1: level_string = "Lava\nLeapers"; break;
    case 2: level_string = "Sumo\nSlammers"; break;
    case 3: level_string = "AstroLoot"; break;
    case 4: level_string = "Paramourus\nRex"; break;
    case 5: level_string = "Arachine"; break;
    case 6: level_string = "Gold...\nJames\nGold"; break;

  }

  sf::RectangleShape box;
  box.setSize(sf::Vector2f(cell_width, cell_height));
  box.setOutlineColor(sf::Color::Black);
  box.setOutlineThickness(4);
  box.setPosition(x,y);


  sf::Text text;
  text.setFont(*(global()->gameEngine.resourceManager->getFont("resources/font/6809 chargen.ttf")));
  text.setCharacterSize(24);
  text.setPosition(x,y+30);
  text.setString(level_string);
  if (position_row == row_position && position_column == column_position){
    //SELECTED
    box.setFillColor(sf::Color(255,255,255,255));
    text.setColor(sf::Color::Red);
  }
  else {
    box.setFillColor(sf::Color::Red);
    text.setColor(sf::Color::White);
  }


  w.draw(box);
  w.draw(text);
}

void BonusLevelMenu::calculateInterval(float window_width, float window_height){
  interval_horizontal = (window_width - margin_left - margin_right - cell_width * num_column)/(num_column - 1);
  if (interval_horizontal < 0)
    interval_horizontal = 0;
  interval_vertical = (window_height - margin_top - margin_down -cell_height * num_row)/(num_row - 1);
  if (interval_vertical < 0)
    interval_vertical = 0;
}
int BonusLevelMenu::getCurrentLevel(){
  return position_row * num_column + position_column + 1;
}

void BonusLevelMenu::receiveInput(constants::Input input, int &state, void *extra_data){
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
        storyMenu.setLevel(getCurrentLevel());
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
  if (position_column < 0) {
    if (position_row > 0){
      position_column = num_column - 1;
      position_row--;
    }
    else{
      state = NonPlaying::LEVELMENU;
      position_column = 0;

    }
  }

  if (position_column >= num_column){
    if (position_row < num_row - 1){
      position_column = 0;
      position_row ++;
    }
    else{
      state  = state = NonPlaying::BONUSLEVELMENU;
      position_column = num_column - 1;
    }
  }
}

LevelMenu::LevelMenu():position_row(0),position_column(0), num_row(3), num_column(3),
cell_width(110), cell_height(95),
margin_left(110), margin_right(115), margin_top(56), margin_down(60),
b_instory(false){
  storyMenu.setBonus(false);
  level_file_map[1] = std::string("resources/levels/level_01.xml"); //this is level 1
  level_file_map[2] = std::string("resources/levels/level_02.xml");
  level_file_map[3] = std::string("resources/levels/level_03.xml");
  level_file_map[4] = std::string("resources/levels/level_04.xml");
  level_file_map[5] = std::string("resources/levels/level_05.xml");
  level_file_map[6] = std::string("resources/levels/level_06.xml");
  level_file_map[7] = std::string("resources/levels/level_07.xml");
  level_file_map[8] = std::string("resources/levels/level_08.xml");
  level_file_map[9] = std::string("resources/levels/level_09.xml");
  level_file_map[10] = std::string("resources/levels/level_Lava.xml");
  level_file_map[11] = std::string("resources/levels/level_sumo.xml");
  level_file_map[12] = std::string("resources/levels/level_space.xml");
  level_file_map[13] = std::string("resources/levels/level_Dino.xml");
  level_file_map[14] = std::string("resources/levels/level_spiders.xml");
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
        storyMenu.setLevel(getCurrentLevel());
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
  if (position_column < 0) {
    if (position_row > 0){
      position_column = num_column - 1;
      position_row--;
    }
    else
      position_column = 0;
  }

  if (position_column >= num_column){
    if (position_row < num_row - 1){
      position_column = 0;
      position_row ++;
    }
    else{
      state  = state = NonPlaying::BONUSLEVELMENU;
      position_column = num_column - 1;
    }
  }
}
void LevelMenu::draw(sf::RenderWindow &w){
  if (b_instory){
    storyMenu.draw(w);
    return;
  }
  //calculateInterval(w.getSize().x, w.getSize().y);
  calculateInterval(800, 600);
  w.clear(sf::Color(0, 0, 0, 255));
  sf::Sprite background;
  background.setTexture(*global()->gameEngine.resourceManager->getTexture("resources/graphics/image/LevelMenu.png"));
  w.draw(background);
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
  box.setOutlineColor(sf::Color::Black);
  box.setOutlineThickness(4);
  box.setPosition(x,y);


  sf::Text text;
  text.setFont(*(global()->gameEngine.resourceManager->getFont("resources/font/6809 chargen.ttf")));
  text.setCharacterSize(24);
  text.setPosition(x+8,y+28);
  text.setString(level_string);
  if (position_row == row_position && position_column == column_position){
    //SELECTED
    box.setFillColor(sf::Color(255,255,255,255));
    text.setColor(sf::Color::Red);
  }
  else {
    box.setFillColor(sf::Color::Red);
    text.setColor(sf::Color::White);
  }


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
        state = NonPlaying::INFOMENU;
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

InfoMenu::InfoMenu():current_index(0), inMenu(false){}
InfoMenu::~InfoMenu(){}
void InfoMenu::receiveInput(constants::Input input, int &state, void *extra_data){
  switch (input) {
    case constants::INPUT_UP:
      current_index--;
      break;
    case constants::INPUT_DOWN:
      current_index++;
      break;
    case constants::INPUT_CONFIRM:
      inMenu = true;
      break;
    case constants::INPUT_ESC:
      if(inMenu){
        inMenu = !inMenu;
      }else{
        state = NonPlaying::MAINMENU;
      }
    default:
      break;
  }
  if (current_index < 0)
    current_index = 0;
  if (current_index > 2)
    current_index = 2;
}
void InfoMenu::draw(sf::RenderWindow &w){
  sf::Sprite sprite;
  sf::Texture *p_texture;
  if(inMenu){
    if (current_index == 0) {
      p_texture= global()->gameEngine.resourceManager->getTexture("resources/graphics/image/controls.png");
    }
    else if (current_index == 1){
      p_texture = global()->gameEngine.resourceManager->getTexture("resources/graphics/image/enemies.png");
    }else{
      p_texture = global()->gameEngine.resourceManager->getTexture("resources/graphics/image/items.png");
    }
  }else {
    if (current_index == 0) {
      p_texture= global()->gameEngine.resourceManager->getTexture("resources/graphics/image/InfoMenu0.png");
    }
    else if (current_index == 1){
      p_texture = global()->gameEngine.resourceManager->getTexture("resources/graphics/image/InfoMenu1.png");
    }else{
      p_texture = global()->gameEngine.resourceManager->getTexture("resources/graphics/image/InfoMenu2.png");
    }
  }
  sprite.setTexture(*p_texture);
  w.draw(sprite);

}

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
  sprite.setPosition(300, 100);
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
      case INFOMENU:
        infoMenu.receiveInput(input,(int &)internal_state);
        return;
      case TERMINALMENU:
        terminalMenu.receiveInput(input, (int &)internal_state);
        return;
      case BONUSLEVELMENU:
        bonusLevelMenu.receiveInput(input, (int &)internal_state);
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
  }else if (internal_state == INFOMENU){
    w.setView(w.getDefaultView()); //reset view
    infoMenu.draw(w);
  }else if (internal_state == BONUSLEVELMENU){
    w.setView(w.getDefaultView()); //reset view
    bonusLevelMenu.draw(w);
  }
}
