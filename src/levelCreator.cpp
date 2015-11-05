#include "levelCreator.h"
#include "xmlParser.h"
#include "typeConversion.h"

#include <string.h>

#include <fstream>
#include <iostream>
#include <sstream>

namespace {
  int getNumberProperty(std::string &str) {
    if ( strcmp(str.c_str(), "moving") == 0){
      return constants::MOVING;
    }
    return -1;
  }


  void getPosition(const char *str, float &x, float &y) {
    std::string line = str;
    std::istringstream is(line);
    std::string part;
    if ( !std::getline(is, part, ';') ) {
      std::cout << "Error: Position is set incorrectly." << std::endl;
      return;
    }
    x = typeconvert::string2float(part);
    if ( !std::getline(is, part, ';') ) {
      std::cout << "Error: Position is set incorrectly." << std::endl;
      return;
    }
    y = typeconvert::string2float(part);
  }

  void getDimensions(const char *str, float &width, float &height) {
    std::string line = str;
    std::istringstream is(line);
    std::string part;
    if ( !std::getline(is, part, ';') ) {
      std::cout << "Error: Dimension is set incorrectly." << std::endl;
      return;
    }
    width = typeconvert::string2float(part);
    if ( !std::getline(is, part, ';') ) {
      std::cout << "Error: Dimension is set incorrectly." << std::endl;
      return;
    }
    height = typeconvert::string2float(part);
  }

  void getPropertySet(const char *str, std::set<int> &propertySet){
    std::string line = str;
    std::istringstream is(line);
    std::string part;
    while ( std::getline(is, part, ';') ) {
      propertySet.insert(getNumberProperty(part));
    }
  }

}

LevelCreator::LevelCreator(EntityManager *m)
  :manager(m), scale(50), eCreator(EntityCreator(m)),
  wallTex(new sf::Texture()),
  tex_player(new sf::Texture()),
  tex_enemy(new sf::Texture())
  {
    wallTex->loadFromFile("resources/wall.png");
    tex_player->loadFromFile("resources/test.png");
    tex_enemy->loadFromFile("resources/dinasaur.png");
  }

LevelCreator::~LevelCreator(){
  clearList();
  delete wallTex;
}


void LevelCreator::loadLevelFile(std::string &fileName) {
  int n;
  float x, y, width, height;
  clearList();
  XMLNode xMainNode=XMLNode::openFileHelper(fileName.c_str());

  //walls
  XMLNode xMap=xMainNode.getChildNode("MAP");
  XMLNode xWalls=xMap.getChildNode("WALLS");

  n = xWalls.nChildNode();
  for (int i=0; i < n; i++) {
    XMLNode xWall = xWalls.getChildNode(i);
    getPosition(xWall.getAttribute("position"), x, y);
    getDimensions(xWall.getAttribute("dimension"), width, height);
    eCreator.createWall(sf::Vector2f( x * scale + 25, y * scale + 25), width*scale, height*scale, wallTex);
    // creation_list.push_back(new levelCreator_internal::WorldComponent(WALL, x, y));
  }

  XMLNode xChars=xMainNode.getChildNode("CHARACTERS");
  //player
  XMLNode xPlayer=xChars.getChildNode("PLAYER");
  getPosition(xPlayer.getAttribute("position"), x, y);
  creation_list.push_back(new levelCreator_internal::WorldComponent(constants::PLAYER, x, y));

  //enemy
  n = xChars.nChildNode("ENEMY");
  for (int i=0; i < n; i++) {
    XMLNode xEnemy = xChars.getChildNode("ENEMY", i);
    getPosition(xEnemy.getAttribute("position"), x, y);
    std::set<int> property_set;
    getPropertySet(xEnemy.getAttribute("property"), property_set);
    if (property_set.find(constants::MOVING) != property_set.end() ) {
      creation_list.push_back(new levelCreator_internal::WorldComponent(constants::ENEMY_MOVING, x, y));
    }
    else {
      creation_list.push_back(new levelCreator_internal::WorldComponent(constants::ENEMY_STATIC, x, y));
    }
  }

}


void LevelCreator::createLevel() {
  for (int i=0; i < creation_list.size(); i++) {
    levelCreator_internal::WorldComponent *c = creation_list[i];
    switch(c->type) {
      case constants::WALL:
        eCreator.create(constants::WALL, sf::Vector2f( c->x * scale + 25, c->y * scale + 25), wallTex);
        break;
      case constants::PLAYER:
        eCreator.create(constants::PLAYER, sf::Vector2f( c->x * scale + 25, c->y * scale + 25), tex_player);
        break;
      case constants::ENEMY_MOVING:
        eCreator.create(constants::ENEMY_MOVING, sf::Vector2f( c->x * scale + 25, c->y * scale + 25), tex_enemy);
        break;
      case constants::ENEMY_STATIC:
        eCreator.create(constants::ENEMY_STATIC, sf::Vector2f( c->x * scale + 25, c->y * scale + 25), tex_enemy);
        break;
      default:
        //do nothing
        break;
    }
  }

}

void LevelCreator::clearList(){
  for (int i=0; i< creation_list.size(); i++)
    delete creation_list[i];
  creation_list.clear();
  creation_list.resize(0);
}
