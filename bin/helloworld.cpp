#include <SFML/Graphics.hpp>
#include "entityManager.h"
#include "graphicsSystem.h"
#include "logicSystem.h"
#include "inputSystem.h"
#include "entityCreator.h"
#include "global.h"

#include <SFML/Audio.hpp>
#include <unistd.h>
#include <iostream>
#include <cmath>




int main(int argc, char** argv)
{
  Global::init();

  srand (time(NULL));
  // create main window
  sf::RenderWindow App(sf::VideoMode(global()->config.appearance.window_width,
    global()->config.appearance.window_height,32), "Hello World - SFML");
  App.setFramerateLimit(60);
  App.setIcon( rIcon.width,  rIcon.height,  rIcon.pixel_data );

  global()->gameEngine.gameState = MENU;

  EntityManager* entityM = new EntityManager();
  GraphicsSystem* graphicsS = new GraphicsSystem(&App, entityM);
  LogicSystem* logicS = new LogicSystem(entityM);
  InputSystem* inputS = new InputSystem(entityM, &App);
  EntityCreator* eCreator = new EntityCreator(entityM);


  sf::Texture *wallTex = new sf::Texture();
  wallTex->loadFromFile("resources/wall.png");
  // eCreator->create(WALL, sf::Vector2f(300,400), wallTex);
  // eCreator->create(WALL, sf::Vector2f(500,500), wallTex);


  for(int i = 0; i < 16; i++){
    eCreator->create(WALL, sf::Vector2f(25 + i*50, 25), wallTex);
    eCreator->create(WALL, sf::Vector2f(25 + i*50, 575), wallTex);
  }
  for(int i = 0; i < 10; i++){
    eCreator->create(WALL, sf::Vector2f(25 , 75+ i*50), wallTex);
    eCreator->create(WALL, sf::Vector2f(775 , 75+ i*50), wallTex);
  }


  eCreator->create(WALL, sf::Vector2f(125 , 375), wallTex);
  eCreator->create(WALL, sf::Vector2f(125 , 225), wallTex);
  eCreator->create(WALL, sf::Vector2f(75 , 375), wallTex);
  eCreator->create(WALL, sf::Vector2f(75 , 225), wallTex);
  eCreator->create(WALL, sf::Vector2f(200 , 375), wallTex);
  eCreator->create(WALL, sf::Vector2f(200 , 225), wallTex);


  eCreator->create(WALL, sf::Vector2f(325 , 375), wallTex);
  eCreator->create(WALL, sf::Vector2f(325 , 225), wallTex);
  eCreator->create(WALL, sf::Vector2f(375 , 375), wallTex);
  eCreator->create(WALL, sf::Vector2f(375 , 225), wallTex);

  eCreator->create(WALL, sf::Vector2f(725 , 375), wallTex);
  eCreator->create(WALL, sf::Vector2f(675 , 375), wallTex);
  eCreator->create(WALL, sf::Vector2f(600 , 375), wallTex);
  eCreator->create(WALL, sf::Vector2f(675 , 225), wallTex);
  eCreator->create(WALL, sf::Vector2f(600 , 225), wallTex);

  // for(int i = 0; i < 15; i++){
  //   eCreator->create(WALL, sf::Vector2f(rand() % 500 + 200, rand() % 300 + 200), wallTex);
  // }

  sf::Texture *tex_player = new sf::Texture();
  tex_player->loadFromFile("resources/test.png");
  eCreator->create(PLAYER, sf::Vector2f(200,300), tex_player);

  sf::Texture *tex_enemy = new sf::Texture();
  tex_enemy->loadFromFile("resources/dinasaur.png");
  eCreator->create(ENEMY_MOVING, sf::Vector2f(400,500), tex_enemy);
  eCreator->create(ENEMY_MOVING, sf::Vector2f(400,100), tex_enemy);
  ((MoveableComponent*)entityM->findEntity(68)->getComponent(MOVEABLE))->setMaxVelocity(75);

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
