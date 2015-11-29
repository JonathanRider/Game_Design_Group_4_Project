#include "nonPlaying.h"
#include "typeConversion.h"
#include <iostream>
#include <string>

LevelMenu::LevelMenu():position_row(0),position_column(0), num_row(3), num_column(3),
cell_width(100), cell_height(80),
margin_left(100), margin_right(100), margin_top(50), margin_down(50){

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
void LevelMenu::receiveInput(constants::Input input, void *extra_data){
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
    case constants::INPUT_CONFIRM:
      if (level_file_map.find(getCurrentLevel()) != level_file_map.end() ){
        global()->gameEngine.entityManager->clearAll();
        global()->gameEngine.levelCreator->loadAndCreateLevel(level_file_map[getCurrentLevel()]);
        global()->gameEngine.gameState = constants::PLAYING;
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
  calculateInterval(w.getSize().x, w.getSize().y);
  //std::cout << w.getSize().x <<"," << w.getSize().y << std::endl;
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
    box.setFillColor(sf::Color(0,0,0,0));
  }
  else {
    box.setFillColor(sf::Color(255,255,255,255));
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

NonPlaying::NonPlaying(){
  sf::Sprite *main_menu0_sprite = new sf::Sprite;
  main_menu0_sprite->setTexture(* global()->gameEngine.resourceManager->getTexture("resources/graphics/image/MainMenu0.png"));
  mainMenuSprites.push_back(main_menu0_sprite);

  sf::Sprite *main_menu1_sprite = new sf::Sprite;
  main_menu1_sprite->setTexture(* global()->gameEngine.resourceManager->getTexture("resources/graphics/image/MainMenu1.png"));
  mainMenuSprites.push_back(main_menu1_sprite);

  sf::Sprite *level_menu0_sprite = new sf::Sprite;
  level_menu0_sprite->setTexture(* global()->gameEngine.resourceManager->getTexture("resources/graphics/image/LevelMenu0.png"));
  levelMenuSprites.push_back(level_menu0_sprite);

  sf::Sprite *level_menu1_sprite = new sf::Sprite;
  level_menu1_sprite->setTexture(* global()->gameEngine.resourceManager->getTexture("resources/graphics/image/LevelMenu1.png"));
  levelMenuSprites.push_back(level_menu1_sprite);

  sf::Sprite *level_menu2_sprite = new sf::Sprite;
  level_menu2_sprite->setTexture(* global()->gameEngine.resourceManager->getTexture("resources/graphics/image/LevelMenu2.png"));
  levelMenuSprites.push_back(level_menu2_sprite);

  gameOverSprite = new sf::Sprite;
  gameOverSprite->setTexture(* global()->gameEngine.resourceManager->getTexture("resources/graphics/image/GameOver.png"));

  winSprite = new sf::Sprite;
  winSprite->setTexture(* global()->gameEngine.resourceManager->getTexture("resources/graphics/image/Win.png"));

}
NonPlaying::~NonPlaying(){}

void NonPlaying::receiveInput(constants::Input input, void *extra_data){
  switch(global()->gameEngine.gameState) {
    case constants::MENU:
            switch (input) {
              case constants::INPUT_UP:
                std::cout << "up" << std::endl;
                if (global()->gameEngine.mainMenuState <= 0) {
                  global()->gameEngine.mainMenuState = 1; //max number of options
                } else {
                  global()->gameEngine.mainMenuState -= 1;
                }
                break;
              case constants::INPUT_DOWN:
              std::cout << "down" << std::endl;
                if (global()->gameEngine.mainMenuState >= 1) {//max number of options
                  global()->gameEngine.mainMenuState = 0;
                } else {
                  global()->gameEngine.mainMenuState += 1;
                }
                break;
              case constants::INPUT_CONFIRM:
              std::cout << "confirm" << std::endl;
                switch(global()->gameEngine.mainMenuState) {
                  case 0: //first menu option
                    std::cout << "levelMenu" << std::endl;
                    global()->gameEngine.gameState = constants::LEVELMENU;
                    break;
                  case 1:  //second menu option
                    global()->gameEngine.gameState = constants::OPTIONSMENU;
                    std::cout << "options" << std::endl;
                    break;
                  default:
                    break;
                }
                break;
              default:
                break;
            }
          return;
        case constants::LEVELMENU:
          /*switch (input) {
            case constants::INPUT_UP:
              if (global()->gameEngine.levelMenuState <= 0) {
                global()->gameEngine.levelMenuState = 2; //max number of options
              } else {
                global()->gameEngine.levelMenuState -= 1;
              }
              break;
            case constants::INPUT_DOWN:
              if (global()->gameEngine.levelMenuState >= 2) {//max number of options
                global()->gameEngine.levelMenuState = 0;
              } else {
                global()->gameEngine.levelMenuState += 1;
              }
              break;
            case constants::INPUT_CONFIRM:
              {
              std::cout << "confirm" << std::endl;
              std::string fileName = ""; //change based on what level is selected
              switch(global()->gameEngine.levelMenuState) {
                case 0: //level 0
                  fileName = "resources/levels/level_01.xml";
                  break;
                case 1:  //level 1
                  fileName = "resources/levels/level_02.xml";
                  break;
                case 2:  //level 2
                  fileName = "resources/levels/level_03.xml";
                  break;
                default:
                  fileName = "resources/levels/level_01.xml";
                  break;
              }
              global()->gameEngine.entityManager->clearAll();
              global()->gameEngine.levelCreator->loadAndCreateLevel(fileName);

              global()->gameEngine.gameState = constants::PLAYING;
            } //end of confirm case
          default:
            break;
          }
          */
          levelMenu.receiveInput(input, NULL);
          return;
        case constants::OPTIONSMENU:
          switch (input) {
            case constants::INPUT_UP:
              if (global()->gameEngine.optionsMenuState <= 0) {
                global()->gameEngine.optionsMenuState = 1; //max number of options
              } else {
                global()->gameEngine.optionsMenuState -= 1;
              }
              break;
            case constants::INPUT_DOWN:
              if (global()->gameEngine.optionsMenuState >= 1) {//max number of options
                global()->gameEngine.optionsMenuState = 0;
              } else {
                global()->gameEngine.optionsMenuState += 1;
              }
              break;
            case constants::INPUT_CONFIRM:
              //do something
              break;
            default:
              break;
          }
          return;
    case constants::GAMEOVER:
      switch (input) {
        case constants::INPUT_CONFIRM:
          global()->gameEngine.gameState = constants::LEVELMENU;
          break;
        default:
          break;
      }
      return;
    case constants::WIN:
      switch (input) {
        case constants::INPUT_CONFIRM:
          global()->gameEngine.gameState = constants::LEVELMENU;
          break;
        default:
          break;
      }
      return;
    default:
      return;
  }
}

void NonPlaying::draw(sf::RenderWindow &w){

  if (global()->gameEngine.gameState == constants::MENU) {

    // sf::Texture *menuTex = new sf::Texture();
    // menuTex->loadFromFile("resources/MainMenu.png");
    // sf::Sprite *menuSprite = new sf::Sprite();
    // menuSprite->setTexture(*menuTex);
    // draw(*menuSprite);
    w.draw(*mainMenuSprites[global()->gameEngine.mainMenuState]);
  } else if (global()->gameEngine.gameState == constants::WIN) {
    w.setView(w.getDefaultView()); //reset view
    w.draw(*winSprite);
  } else if (global()->gameEngine.gameState == constants::GAMEOVER) {
    w.setView(w.getDefaultView()); //reset view
    w.draw(*gameOverSprite);
  } else if (global()->gameEngine.gameState == constants::LEVELMENU) {
    w.setView(w.getDefaultView()); //reset view
    //w.draw(*(levelMenuSprites.at(global()->gameEngine.levelMenuState)));
    levelMenu.draw(w);
  }
}
