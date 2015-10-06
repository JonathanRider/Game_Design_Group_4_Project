#include <SFML/Graphics.hpp>
#include "entityManager.h"
#include "graphicsSystem.h"
#include "logicSystem.h"
#include "inputSystem.h"

#include <SFML/Audio.hpp>

#include <iostream>

int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Hello World - SFML");

  //testing graphics with shape
  sf::RectangleShape *shape = new sf::RectangleShape(sf::Vector2f(50, 50));

  //load texture
  sf::Texture texture;
  texture.loadFromFile("resources/test.png");
  //create sprite
  sf::Sprite *sprite = new sf::Sprite();
  sprite->setTexture(texture);

  EntityManager* entityM = new EntityManager();
  GraphicsSystem* graphicsS = new GraphicsSystem(&App, entityM, MENU);
  LogicSystem* logicS = new LogicSystem(entityM, MENU);
  InputSystem* inputS = new InputSystem(entityM, MENU);


  GraphicsComponent* gc = new GraphicsComponent(sprite);
  ControllableComponent* cc = new ControllableComponent();



  Entity helloEntity =  Entity(1); //random id for now
  helloEntity.addComponent(gc);
  helloEntity.addComponent(cc);
  entityM->addEntity(helloEntity);

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
