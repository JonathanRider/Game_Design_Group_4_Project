#include <SFML/Graphics.hpp>
#include "entityManager.h"
#include "graphicsSystem.h"
#include "logicSystem.h"
#include "inputSystem.h"
#include "entityCreator.h"
#include "global.h"
#include "levelCreator.h"

#include <SFML/Audio.hpp>
#include <unistd.h>
#include <iostream>
#include <cmath>
#include <string>




int main(int argc, char** argv)
{
  Global::init();

  srand (time(NULL));
  // create main window
  sf::RenderWindow App(sf::VideoMode(global()->config.appearance.window_width,
    global()->config.appearance.window_height,32), "Hello World - SFML");
  App.setFramerateLimit(60);
  App.setIcon( constants::rIcon.width,  constants::rIcon.height,  constants::rIcon.pixel_data );

  global()->gameEngine.gameState = constants::MENU;
  //global()->gameEngine.gameState = constants::PLAYING;
  global()->gameEngine.mainMenuState = 0;
  global()->gameEngine.levelMenuState = 0;
  global()->gameEngine.optionsMenuState = 0;

  EntityManager* entityM = new EntityManager();
  LevelCreator *lCreator = new LevelCreator(entityM);
  GraphicsSystem* graphicsS = new GraphicsSystem(&App, entityM);
  LogicSystem* logicS = new LogicSystem(entityM, lCreator);
  global()->gameEngine.logicSystem = logicS;
  InputSystem* inputS = new InputSystem(entityM, &App, lCreator);;
  EntityCreator* eCreator = new EntityCreator(entityM);
  global()->gameEngine.entityCreator = eCreator;

//  std::string fileName = "resources/levels/level_01.xml";
//  lCreator->loadLevelFile(fileName);
//  lCreator->createLevel();
  float secondCounter = 0;

  sf::Clock graphicsTimer;
  sf::Clock inputTimer;
  sf::Clock logicTimer;
  // start main loop

  while(global()->gameEngine.gameState != constants::CLOSING)
  {
    App.clear(sf::Color::Black);

    float dTime = inputTimer.restart().asSeconds();
    secondCounter += dTime;
    if(secondCounter > 1){
      secondCounter--;
      // std::cout << "fps: " << 1/dTime << std::endl;
    }

    inputS->update(dTime);

    dTime = logicTimer.restart().asSeconds();
    logicS->update(dTime);

    dTime = graphicsTimer.restart().asSeconds();
    graphicsS->update(dTime);

    // display
    App.display();
  }
  App.close();
  // Done.
  return 0;
}
