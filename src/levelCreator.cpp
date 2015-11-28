#include "levelCreator.h"
#include "xmlParser.h"
#include "typeConversion.h"
#include "global.h"

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

  void getStringList(const char *str, std::vector<std::string> &string_list) {
    std::string line = str;
    std::istringstream is(line);
    std::string part;
    while ( std::getline(is, part, ';') ) {
      string_list.push_back(part);
    }
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
  :manager(m), scale(50), eCreator(EntityCreator(m)){}

LevelCreator::~LevelCreator(){
  clearList();
}


void LevelCreator::loadLevelFile(std::string &fileName) {
  int n;
  float x, y, width, height;
  std::string sprite_file_name;
  clearList();
  XMLNode xMainNode=XMLNode::openFileHelper(fileName.c_str());

  //music
  { //don't want to contaminate other variables
    XMLNode xMusic=xMainNode.getChildNode("MUSIC");
    std::vector<std::string> string_list;
    getStringList(xMusic.getAttribute("file"), string_list);
    global()->gameEngine.audioSystem->reset();
    global()->gameEngine.audioSystem->clearMusicList();
    global()->gameEngine.audioSystem->addMusicList(string_list);
  }

  //walls
  XMLNode xMap=xMainNode.getChildNode("MAP");
  XMLNode xWalls=xMap.getChildNode("WALLS");

  n = xWalls.nChildNode();
  for (int i=0; i < n; i++) {
    XMLNode xWall = xWalls.getChildNode(i);
    getPosition(xWall.getAttribute("position"), x, y);
    getDimensions(xWall.getAttribute("dimension"), width, height);
    sprite_file_name = xWall.getAttribute("sprite") == NULL?"": xWall.getAttribute("sprite");
    eCreator.createWall(sf::Vector2f( x * scale + 25, y * scale + 25), width*scale, height*scale, sprite_file_name);
    // creation_list.push_back(new levelCreator_internal::WorldComponent(WALL, x, y));
  }

  //destroyable boxes
  XMLNode xBoxes=xMap.getChildNode("BOXES");
  n = xBoxes.nChildNode();
  for (int i=0; i < n; i++) {
    XMLNode xBox = xBoxes.getChildNode(i);
    getPosition(xBox.getAttribute("position"), x, y);
    sprite_file_name = xBox.getAttribute("sprite") == NULL?"": xBox.getAttribute("sprite");
    eCreator.createBox(sf::Vector2f( x * scale + 25, y * scale + 25), sprite_file_name);
    // creation_list.push_back(new levelCreator_internal::WorldComponent(WALL, x, y));
  }

  //finish
  XMLNode xFinish = xMap.getChildNode("FINISH");
  getPosition(xFinish.getAttribute("position"), x, y);
  sprite_file_name = xFinish.getAttribute("sprite") == NULL?"": xFinish.getAttribute("sprite");
  //getDimensions(xWall.getAttribute("dimension"), width, height);
  creation_list.push_back(new levelCreator_internal::WorldComponent(constants::FINISH, x, y, sprite_file_name));

  //traps
  XMLNode xTraps = xMap.getChildNode("TRAPS");
  n = xTraps.nChildNode("TRAP");
  for (int i=0; i < n; i++) {
    XMLNode xTrap = xTraps.getChildNode(i);
    getPosition(xTrap.getAttribute("position"), x, y);
    sprite_file_name = xTrap.getAttribute("sprite") == NULL?"": xTrap.getAttribute("sprite");
    creation_list.push_back(new levelCreator_internal::WorldComponent(constants::TRAP, x, y, sprite_file_name));
  }

  XMLNode xChars=xMainNode.getChildNode("CHARACTERS");
  //player
  XMLNode xPlayer=xChars.getChildNode("PLAYER");
  getPosition(xPlayer.getAttribute("position"), x, y);
  sprite_file_name = xPlayer.getAttribute("sprite") == NULL?"": xPlayer.getAttribute("sprite");
  creation_list.push_back(new levelCreator_internal::WorldComponent(constants::PLAYER, x, y, sprite_file_name));

  //enemy
  n = xChars.nChildNode("ENEMY");
  for (int i=0; i < n; i++) {
    XMLNode xEnemy = xChars.getChildNode("ENEMY", i);
    getPosition(xEnemy.getAttribute("position"), x, y);
    sprite_file_name = xEnemy.getAttribute("sprite") == NULL?"": xEnemy.getAttribute("sprite");
    std::set<int> property_set;
    getPropertySet(xEnemy.getAttribute("property"), property_set);
    if (property_set.find(constants::MOVING) != property_set.end() ) {
      creation_list.push_back(new levelCreator_internal::WorldComponent(constants::ENEMY_MOVING, x, y, sprite_file_name));
    }
    else {
      creation_list.push_back(new levelCreator_internal::WorldComponent(constants::ENEMY_STATIC, x, y, sprite_file_name));
    }
  }

  {//INVENTORY
    XMLNode xInv=xMainNode.getChildNode("INVENTORY");
    n = xInv.nChildNode("BULLET");
    std::map<std::string, std::string> item_list;
    for (int i=0; i < n; i++){
      XMLNode xBullet=xInv.getChildNode("BULLET", i);
      item_list.insert(std::pair<std::string,std::string>(xBullet.getAttribute("type"),xBullet.getAttribute("quantity")));
    }
    eCreator.createInventory(sf::Vector2f(0,0),item_list);
  }

}


void LevelCreator::createLevel() {

  for (int i=0; i < creation_list.size(); i++) {
    levelCreator_internal::WorldComponent *c = creation_list[i];
    switch(c->type) {
      case constants::WALL:
        eCreator.create(constants::WALL, sf::Vector2f( c->x * scale + 25, c->y * scale + 25), c->sprite_file_name);
        break;
      case constants::PLAYER:
        eCreator.create(constants::PLAYER, sf::Vector2f( c->x * scale + 25, c->y * scale + 25), c->sprite_file_name);
        break;
      case constants::FINISH:
        eCreator.create(constants::FINISH, sf::Vector2f( c->x * scale + 25, c->y * scale + 25), c->sprite_file_name);
        break;
      case constants::TRAP:
        eCreator.create(constants::TRAP, sf::Vector2f( c->x * scale + 25, c->y * scale + 25), c->sprite_file_name);
        break;
      case constants::ENEMY_MOVING:
        eCreator.create(constants::ENEMY_MOVING, sf::Vector2f( c->x * scale + 25, c->y * scale + 25), c->sprite_file_name);
        break;
      case constants::ENEMY_STATIC:
        eCreator.create(constants::ENEMY_STATIC, sf::Vector2f( c->x * scale + 25, c->y * scale + 25), c->sprite_file_name);
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
