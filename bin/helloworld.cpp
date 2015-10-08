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

   App.setIcon( rIcon.width,  rIcon.height,  rIcon.pixel_data );
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

  Entity wall = Entity(2);
  GraphicsComponent* wallgc = new GraphicsComponent(sprite);
  CollidableComponent* colc = new CollidableComponent(sf::Vector2f(400.0, 400.0), 50.0, 50.0);
  wall.addComponent(wallgc);
  wall.addComponent(colc);
  wall.setXY(sf::Vector2f(400.0, 400.0));

  Entity wall2 = Entity(3);
  wall2.setXY(sf::Vector2f(400.0, 420.0));
  CollidableComponent* colc2 = new CollidableComponent(wall2.getXY(), 50.0, 50.0);
  GraphicsComponent* wallgc2 = new GraphicsComponent(sprite);
  wall2.addComponent(wallgc2);
  wall2.addComponent(colc2);

  Entity helloEntity =  Entity(1); //random id for now
  GraphicsComponent* gc = new GraphicsComponent(sprite);
  ControllableComponent* cc = new ControllableComponent();
  MoveableComponent* mc = new MoveableComponent(1200.0,80000.0, 300.0); //accel, decel, max speed
  CollidableComponent* playerc = new CollidableComponent(sf::Vector2f(0.0,0.0), 50.0, 50.0);
  helloEntity.addComponent(gc);
  helloEntity.addComponent(cc);
  helloEntity.addComponent(mc);
  helloEntity.addComponent(playerc);



  entityM->addEntity(helloEntity);
  entityM->addEntity(wall);
  entityM->addEntity(wall2);

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
