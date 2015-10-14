#include <SFML/Graphics.hpp>
#include "entityManager.h"
#include "graphicsSystem.h"
#include "logicSystem.h"
#include "inputSystem.h"
#include "entityCreator.h"

#include <SFML/Audio.hpp>
#include <unistd.h>
#include <iostream>



int main(int argc, char** argv)
{
  srand (time(NULL));
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Hello World - SFML");
  App.setFramerateLimit(60);
  App.setIcon( rIcon.width,  rIcon.height,  rIcon.pixel_data );

  EntityManager* entityM = new EntityManager();
  GraphicsSystem* graphicsS = new GraphicsSystem(&App, entityM, MENU);
  LogicSystem* logicS = new LogicSystem(entityM, MENU);
  InputSystem* inputS = new InputSystem(entityM, MENU, &App);



  EntityCreator* eCreator = new EntityCreator(entityM);
  sf::Texture *wallTex = new sf::Texture();
  wallTex->loadFromFile("resources/wall.png");
  eCreator->create(WALL, sf::Vector2f(300,400), wallTex);
  eCreator->create(WALL, sf::Vector2f(500,500), wallTex);


  for(int i = 0; i < 16; i++){
    eCreator->create(WALL, sf::Vector2f(25 + i*50, 25), wallTex);
    eCreator->create(WALL, sf::Vector2f(25 + i*50, 575), wallTex);
  }
  for(int i = 0; i < 10; i++){
    eCreator->create(WALL, sf::Vector2f(25 , 75+ i*50), wallTex);
    eCreator->create(WALL, sf::Vector2f(775 , 75+ i*50), wallTex);
  }

  for(int i = 0; i < 15; i++){
    eCreator->create(WALL, sf::Vector2f(rand() % 500 + 200, rand() % 300 + 200), wallTex);
  }

  sf::Texture *tex = new sf::Texture();
  tex->loadFromFile("resources/test.png");
  eCreator->create(PLAYER, sf::Vector2f(200,300), tex);



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

    }

    // clear screen and fill with blue
    App.clear(sf::Color::Blue);

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
    //App.draw(shape);

    // display
    App.display();
  }

  // Done.
  return 0;
}
