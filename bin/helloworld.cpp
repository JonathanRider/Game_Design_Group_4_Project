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

  EntityManager* entityM = new EntityManager();
  GraphicsSystem* graphicsS = new GraphicsSystem(&App, entityM);
  LogicSystem* logicS = new LogicSystem(entityM);
  InputSystem* inputS = new InputSystem(entityM, &App);
  EntityCreator* eCreator = new EntityCreator(entityM);
  LevelCreator *lCreator = new LevelCreator(entityM);
  std::string fileName = "resources/levels/level_01.xml";
  lCreator->loadLevelFile(fileName);
  lCreator->createLevel();

  sf::Texture *tex_bullet = new sf::Texture();
  tex_bullet->loadFromFile("resources/bullet.png");

  float secondCounter = 0;

  sf::Clock graphicsTimer;
  sf::Clock inputTimer;
  sf::Clock logicTimer;
  // start main loop
  while(App.isOpen())
  {
    // process events
    sf::Event Event;
    while(App.pollEvent(Event))
    {

      // Exit
      if(Event.type == sf::Event::Closed)
        App.close();

      //handle one time key presses
      if (Event.type == sf::Event::KeyPressed){
        inputS->handleKeyPress(Event);
      }

      //remove this once input system can handle it
      if (Event.type == sf::Event::MouseButtonPressed){
        if (Event.mouseButton.button == sf::Mouse::Left){


          float dy = entityM->getPlayer()->getXY().y - Event.mouseButton.y;
          float dx = entityM->getPlayer()->getXY().x - Event.mouseButton.x;
          float direction =  180 - atan2(dy, dx) * 180 / PI;
          eCreator->createGrenade(entityM->getPlayer()->getXY(), direction, 1000, 500, tex_bullet);



        }
        inputS->handleClick(Event);
      }

    }

    // clear screen and fill with blue
    App.clear(sf::Color::Blue);

    float dTime = inputTimer.restart().asSeconds();
    secondCounter += dTime;
    if(secondCounter > 1){
      secondCounter--;
      // std::cout << "fps: " << 1/dTime << std::endl;
    }


    //uncomment for rapid fire
    //


      if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
        float dy = entityM->getPlayer()->getXY().y - sf::Mouse::getPosition(App).y;
        float dx = entityM->getPlayer()->getXY().x - sf::Mouse::getPosition(App).x;
        float direction =  180 - atan2(dy, dx) * 180 / PI;
        eCreator->createGrenade(entityM->getPlayer()->getXY(), direction, 1000, 500, tex_bullet);

      }


    inputS->update(dTime);
    dTime = logicTimer.restart().asSeconds();
    logicS->update(dTime);
    dTime = graphicsTimer.restart().asSeconds();
    graphicsS->update(dTime);
    //App.draw(shape);

    // display
    App.display();
  }

  // Done.
  return 0;
}
