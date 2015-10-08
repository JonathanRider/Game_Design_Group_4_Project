#include "prefabs.h"
#include "constants.h"
#include <iostream>

namespace prefabs{

  int curID = 1;
  int getNewID(){return curID++;}


  sf::Texture *playerTexture;

  Entity* newPlayer(float x, float y){
    Entity *player = new Entity(getNewID());
    player->setXY(sf::Vector2f(x, y));

    //load texture
    if(playerTexture == NULL){
      playerTexture = new sf::Texture();
      playerTexture->loadFromFile("resources/test.png");
    }
    //create sprite
    sf::Sprite *sprite = new sf::Sprite();
    sprite->setTexture(*playerTexture);

    GraphicsComponent* gc = new GraphicsComponent(sprite);
    ControllableComponent* cc = new ControllableComponent();
    MoveableComponent* mc = new MoveableComponent(1200.0,80000.0, 300.0); //accel, decel, max speed
    CollidableComponent* playerc = new CollidableComponent(player->getXY(), 50.0, 50.0);


    player->addComponent(gc);
    player->addComponent(cc);
    player->addComponent(mc);
    player->addComponent(playerc);
    return player;
  }


  sf::Texture *wallTexture;
  Entity* newWall(float x, float y){
    Entity *wall = new Entity(getNewID());
    wall->setXY(sf::Vector2f(x, y));
    //load texture
    if(wallTexture == NULL){
      wallTexture = new sf::Texture();
      wallTexture->loadFromFile("resources/test.png");
    }
    //create sprite
    sf::Sprite *sprite = new sf::Sprite();
    sprite->setTexture(*wallTexture);
    GraphicsComponent* gc = new GraphicsComponent(sprite);
    CollidableComponent* wallc = new CollidableComponent(wall->getXY(), 50.0, 50.0);

    wall->addComponent(gc);
    wall->addComponent(wallc);


    return wall;
  }


}
