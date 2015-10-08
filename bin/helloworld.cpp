#include <SFML/Graphics.hpp>
#include "entityManager.h"
#include "graphicsSystem.h"
#include "logicSystem.h"
#include "inputSystem.h"
#include "prefabs.h"

#include <SFML/Audio.hpp>

#include <iostream>

int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Hello World - SFML");
  App.setIcon( rIcon.width,  rIcon.height,  rIcon.pixel_data );

  EntityManager* entityM = new EntityManager();
  GraphicsSystem* graphicsS = new GraphicsSystem(&App, entityM, MENU);
  LogicSystem* logicS = new LogicSystem(entityM, MENU);
  InputSystem* inputS = new InputSystem(entityM, MENU);



  entityM->addEntity(*prefabs::newPlayer(50,50));
  entityM->addEntity(*prefabs::newWall(400, 400));
  entityM->addEntity(*prefabs::newWall(400, 420));

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

    }

    // clear screen and fill with blue
    App.clear(sf::Color::Blue);

    float dTime = graphicsTimer.restart().asSeconds();
    graphicsS->update(dTime);
    dTime = logicTimer.restart().asSeconds();
    logicS->update(dTime);
    dTime = inputTimer.restart().asSeconds();
    inputS->update(dTime);
    //App.draw(shape);

    // display
    App.display();
  }

  // Done.
  return 0;
}
