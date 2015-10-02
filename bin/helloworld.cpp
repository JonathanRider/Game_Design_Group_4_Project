#include <SFML/Graphics.hpp>
#include "entityManager.h"
#include "graphicsSystem.h"

#include <iostream>

int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Hello World - SFML");

  sf::RectangleShape *shape = new sf::RectangleShape(sf::Vector2f(50, 50));

  entityManager* entityM = new entityManager();
  graphicsSystem* graphicsS = new graphicsSystem(&App, entityM, 1);

  graphicsComponent* gc = new graphicsComponent(shape);


  entity helloEntity =  entity(1); //random id for now
  helloEntity.addComponent(gc);
  entityM->addEntity(helloEntity);


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
    }

    // clear screen and fill with blue
    App.clear(sf::Color::Blue);
    graphicsS->update(1.0);
    //App.draw(shape);

    // display
    App.display();
  }

  // Done.
  return 0;
}
