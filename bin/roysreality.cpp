#include <SFML/Graphics.hpp>
#include "entityManager.h"
#include "graphicsSystem.h"
#include "logicSystem.h"
#include "inputSystem.h"
#include "entityCreator.h"
#include "global.h"
#include "levelCreator.h"
#include "audioSystem.h"
#include "resourceManager.h"
#include "nonPlaying.h"

#include <unistd.h>
#include <iostream>
#include <cmath>
#include <string>




int main(int argc, char** argv)
{
  Global::init();
  global()->gameEngine.gameState = constants::NONPLAYING;
  //global()->gameEngine.gameState = constants::PLAYING;
  srand (time(NULL));
  // create main window
  sf::RenderWindow App(sf::VideoMode(global()->config.appearance.window_width,
    global()->config.appearance.window_height,32), "Roy's Reality");
  App.setFramerateLimit(60);
  App.setIcon( constants::rIcon.width,  constants::rIcon.height,  constants::rIcon.pixel_data );


  ResourceManager *resourceM = new ResourceManager();
  global()->gameEngine.resourceManager = resourceM;

  EntityManager* entityM = new EntityManager();
  global()->gameEngine.entityManager = entityM;
  LevelCreator *lCreator = new LevelCreator(entityM);
  global()->gameEngine.levelCreator = lCreator;
  GraphicsSystem* graphicsS = new GraphicsSystem(&App, entityM);
  global()->gameEngine.graphicsSystem = graphicsS;
  AudioSystem* audioS = new AudioSystem();
  global()->gameEngine.audioSystem = audioS;


  LogicSystem* logicS = new LogicSystem(entityM, lCreator);
  global()->gameEngine.logicSystem = logicS;
  InputSystem* inputS = new InputSystem(entityM, &App, lCreator);;
  EntityCreator* eCreator = new EntityCreator(entityM);
  global()->gameEngine.entityCreator = eCreator;
  NonPlaying * nonPlaying = new NonPlaying();
  global()->gameEngine.nonPlaying = nonPlaying;

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

    audioS->update();

    // display
    App.display();
  }
  App.close();


  delete nonPlaying;
  delete eCreator;
  delete inputS;
  delete logicS;
  delete audioS;
  delete graphicsS;
  delete lCreator;
  delete entityM;
  delete resourceM;
  Global::clean();
  // Done.
  return 0;
}
