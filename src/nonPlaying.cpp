#include "nonPlaying.h"
#include <iostream>
#include <string>
#include <string.h>

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

LevelMenu::Page::Page(int row, int col):
n_row(row),n_col(col), cell_width(110), cell_height(95),
margin_left(110), margin_right(115), margin_top(56), margin_down(60), selected_row(0), selected_col(0),text_x_offset(8),text_y_offset(28)
{
  level_display_list.resize(n_row * n_col);
  calculateInterval(800, 600);
}
LevelMenu::Page::~Page(){}
void LevelMenu::Page::setBackgroundTexture(const char *texture_file){
  background_sprite.setTexture(*(global()->gameEngine.resourceManager->getTexture(texture_file)));
}
void LevelMenu::Page::setPageParameters(const char *name, float value){
  if (strcmp("CELL_WIDTH", name) == 0){
    cell_width = value;
  } else if (strcmp("CELL_HEIGHT", name) == 0){
    cell_height = value;
  } else if (strcmp("MARGIN_LEFT", name) == 0){
    margin_left = value;
  } else if (strcmp("MARGIN_RIGHT", name) == 0){
    margin_right = value;
  } else if (strcmp("MARGIN_TOP", name) == 0){
    margin_top = value;
  } else if (strcmp("MARGIN_DOWN", name) == 0){
    margin_down = value;
  } else if (strcmp("TEXT_X_OFFSET", name) == 0){
    text_x_offset = value;
  } else if (strcmp("TEXT_Y_OFFSET", name) == 0){
    text_y_offset = value;
  }
  calculateInterval(800,600);
}
void LevelMenu::Page::setLevelDisplayString(int level, const char *str){
  level_display_list[level - 1] = str;
}
void LevelMenu::Page::draw(sf::RenderWindow &w){
  w.clear(sf::Color(0, 0, 0, 255));
  w.draw(background_sprite);
  for(int i=0; i < n_row; i++)
    for(int j=0; j < n_col; j++){
      if (i == selected_row && j == selected_col)
        drawCell(w,i,j,true);
      else
        drawCell(w,i,j,false);
    }
}
void LevelMenu::Page::drawCell(sf::RenderWindow &w, int row_position, int column_position, bool b_selected){
  float x, y;
  //calculate the position
  x = margin_left + (cell_width + interval_horizontal) * column_position;
  y = margin_top + (cell_height + interval_vertical) * row_position;

  sf::RectangleShape box;
  box.setSize(sf::Vector2f(cell_width, cell_height));
  box.setOutlineColor(sf::Color::Black);
  box.setOutlineThickness(4);
  box.setPosition(x,y);

  sf::Text text;
  text.setFont(*(global()->gameEngine.resourceManager->getFont("resources/font/6809 chargen.ttf")));
  text.setCharacterSize(24);
  text.setPosition(x+text_x_offset,y+text_y_offset);
  text.setString(level_display_list[row_position * n_col + column_position]);
  if (b_selected){
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
void LevelMenu::Page::calculateInterval(float window_width, float window_height){
  interval_horizontal = (window_width - margin_left - margin_right - cell_width * n_col)/(n_col - 1);
  if (interval_horizontal < 0)
    interval_horizontal = 0;
  interval_vertical = (window_height - margin_top - margin_down -cell_height * n_row)/(n_row - 1);
  if (interval_vertical < 0)
    interval_vertical = 0;
}
int LevelMenu::Page::move(const char *direction){
  if (strcmp(direction, "UP") == 0){
    selected_row --;
  }
  else if (strcmp(direction, "DOWN") == 0){
    selected_row ++;
  }
  else if (strcmp(direction, "LEFT") == 0 ){
    selected_col --;
  }
  else if (strcmp(direction, "RIGHT") == 0){
    selected_col ++;
  }
  if (selected_row < 0)
    selected_row = 0;
  if (selected_row >= n_row)
    selected_row = n_row - 1;
  if (selected_col < 0) {
    if (selected_row > 0){
      selected_col = n_col - 1;
      selected_row--;
    }
    else
      selected_col = 0;
      return -1; //move to previous page
  }
  if (selected_col >= n_col){
    if (selected_row < n_row - 1){
      selected_col = 0;
      selected_row ++;
    }
    else{
      selected_col = n_col - 1;
      return 1; //move to next page
    }
  }
  return 0;
}
LevelMenu::LevelMenu():b_instory(false), current_page(0)
{
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
  level_file_map[15] = std::string("resources/levels/level_bond.xml");


  page_list.push_back(new Page(3,3));
  page_list[0]->setBackgroundTexture("resources/graphics/image/LevelMenu.png");
  page_list[0]->setLevelDisplayString(1, "Level 1");
  page_list[0]->setLevelDisplayString(2, "Level 2");
  page_list[0]->setLevelDisplayString(3, "Level 3");
  page_list[0]->setLevelDisplayString(4, "Level 4");
  page_list[0]->setLevelDisplayString(5, "Level 5");
  page_list[0]->setLevelDisplayString(6, "Level 6");
  page_list[0]->setLevelDisplayString(7, "Level 7");
  page_list[0]->setLevelDisplayString(8, "Level 8");
  page_list[0]->setLevelDisplayString(9, "Level 9");

  page_list.push_back(new Page(2,3));
  page_list[1]->setPageParameters("CELL_WIDTH", 160);
  page_list[1]->setPageParameters("CELL_HEIGHT", 160);
  page_list[1]->setPageParameters("TEXT_X_OFFSET", 0);
  page_list[1]->setPageParameters("TEXT_Y_OFFSET", 30);
  page_list[1]->setLevelDisplayString(1, "Lava\nLeapers");
  page_list[1]->setLevelDisplayString(2, "Sumo\nSlammers");
  page_list[1]->setLevelDisplayString(3, "AstroLoot");
  page_list[1]->setLevelDisplayString(4, "Paramourus\nRex");
  page_list[1]->setLevelDisplayString(5, "Arachine");
  page_list[1]->setLevelDisplayString(6, "Gold...\nJames\nGold");
}
LevelMenu::~LevelMenu(){}
int LevelMenu::getCurrentLevel(){
  if (current_page == 0)
    return page_list[0]->getCurrentLevel();
  else
    return 3 * 3 + page_list[1]->getCurrentLevel();
}
void LevelMenu::receiveInput(constants::Input input, int &state, void *extra_data){
  if (b_instory){
    storyMenu.receiveInput(input, state, &b_instory);
    return;
  }
  switch (input) {
    case constants::INPUT_UP:
      current_page += page_list[current_page]->move("UP");
      break;
    case constants::INPUT_DOWN:
      current_page += page_list[current_page]->move("DOWN");
      break;
    case constants::INPUT_LEFT:
      current_page += page_list[current_page]->move("LEFT");
      break;
    case constants::INPUT_RIGHT:
      current_page += page_list[current_page]->move("RIGHT");
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
  if (current_page < 0){
    current_page = 0;
  }
  if (current_page >= page_list.size()){
    current_page = page_list.size() - 1;
  }

}
void LevelMenu::draw(sf::RenderWindow &w){
  if (b_instory){
    storyMenu.draw(w);
    return;
  }
  page_list[current_page]->draw(w);
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
      p_texture= global()->gameEngine.resourceManager->getTexture("resources/graphics/image/infomenu0.png");
    }
    else if (current_index == 1){
      p_texture = global()->gameEngine.resourceManager->getTexture("resources/graphics/image/infomenu1.png");
    }else{
      p_texture = global()->gameEngine.resourceManager->getTexture("resources/graphics/image/infomenu2.png");
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
  }
}
