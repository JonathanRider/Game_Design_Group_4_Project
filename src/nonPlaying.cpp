#include "nonPlaying.h"
#include <iostream>

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
          switch (input) {
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
    w.draw(*(levelMenuSprites.at(global()->gameEngine.levelMenuState)));
  }
}
