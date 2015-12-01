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

  void getFloat(const char *str, float &num){
    std::string line = str;
    std::istringstream is(line);
    std::string part;
    if ( !std::getline(is, part) ) {
      std::cout << "Error: Dimension is set incorrectly." << std::endl;
      return;
    }
    num = typeconvert::string2float(part);
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

LevelCreator::~LevelCreator(){}


void LevelCreator::loadAndCreateLevel(std::string &fileName) {
  int n;
  float x, y, width, height;
  std::string sprite_file_name;
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
  XMLNode xMap=xMainNode.getChildNode("MAP");

  {
    //Glass Walls
    XMLNode xGlassWalls=xMap.getChildNode("GLASSWALLS");
    n = xGlassWalls.nChildNode();
    for (int i=0; i < n; i++) {
      XMLNode xGlass = xGlassWalls.getChildNode(i);
      getPosition(xGlass.getAttribute("position"), x, y);
      getDimensions(xGlass.getAttribute("dimension"), width, height);
      sprite_file_name = xGlass.getAttribute("sprite") == NULL?"": xGlass.getAttribute("sprite");
      eCreator.createGlass(sf::Vector2f( x * scale + 25, y * scale + 25), width*scale, height*scale, sprite_file_name);
    }
  }
  
  {
    //walls
    XMLNode xWalls=xMap.getChildNode("WALLS");

    n = xWalls.nChildNode();
    for (int i=0; i < n; i++) {
      XMLNode xWall = xWalls.getChildNode(i);
      getPosition(xWall.getAttribute("position"), x, y);
      getDimensions(xWall.getAttribute("dimension"), width, height);
      sprite_file_name = xWall.getAttribute("sprite") == NULL?"": xWall.getAttribute("sprite");
      eCreator.createWall(sf::Vector2f( x * scale + 25, y * scale + 25), width*scale, height*scale, sprite_file_name);
    }
  }

  {
    //destroyable boxes
    XMLNode xBoxes=xMap.getChildNode("BOXES");
    n = xBoxes.nChildNode();
    for (int i=0; i < n; i++) {
      XMLNode xBox = xBoxes.getChildNode(i);
      getPosition(xBox.getAttribute("position"), x, y);
      sprite_file_name = xBox.getAttribute("sprite") == NULL?"": xBox.getAttribute("sprite");
      eCreator.createBox(sf::Vector2f( x * scale + 25, y * scale + 25), sprite_file_name);
    }
  }


  {
    //finish
    XMLNode xFinish = xMap.getChildNode("FINISH");
    getPosition(xFinish.getAttribute("position"), x, y);
    sprite_file_name = xFinish.getAttribute("sprite") == NULL?"": xFinish.getAttribute("sprite");
    eCreator.create(constants::FINISH, sf::Vector2f( x * scale + 25, y * scale + 25), sprite_file_name);
  }

  {
    //traps
    XMLNode xTraps = xMap.getChildNode("TRAPS");
    n = xTraps.nChildNode("TRAP");
    for (int i=0; i < n; i++) {
      XMLNode xTrap = xTraps.getChildNode(i);
      getPosition(xTrap.getAttribute("position"), x, y);
      sprite_file_name = xTrap.getAttribute("sprite") == NULL?"": xTrap.getAttribute("sprite");
      eCreator.create(constants::TRAP, sf::Vector2f( x * scale + 25, y * scale + 25), sprite_file_name);
    }
  }


  XMLNode xChars=xMainNode.getChildNode("CHARACTERS");

  {
    //player
    XMLNode xPlayer=xChars.getChildNode("PLAYER");
    getPosition(xPlayer.getAttribute("position"), x, y);
    sprite_file_name = xPlayer.getAttribute("sprite") == NULL?"": xPlayer.getAttribute("sprite");
    eCreator.create(constants::PLAYER, sf::Vector2f( x * scale + 25, y * scale + 25), sprite_file_name);
  }

  //enemy
  {
    n = xChars.nChildNode("ENEMY");
    for (int i=0; i < n; i++) {
      XMLNode xEnemy = xChars.getChildNode("ENEMY", i);
      getPosition(xEnemy.getAttribute("position"), x, y);
      sprite_file_name = xEnemy.getAttribute("sprite") == NULL?"": xEnemy.getAttribute("sprite");
      std::set<int> property_set;
      float viewAngle, viewDirection, viewDistance;
      getFloat(xEnemy.getAttribute("viewangle"), viewAngle);
      getFloat(xEnemy.getAttribute("viewdirection"), viewDirection);
      getFloat(xEnemy.getAttribute("viewdistance"), viewDistance);
      getPropertySet(xEnemy.getAttribute("property"), property_set);
      if (property_set.find(constants::MOVING) != property_set.end() ) {
        float left, right, up, down, moveDirection;
        getFloat(xEnemy.getAttribute("left"), left);
        getFloat(xEnemy.getAttribute("right"), right);
        getFloat(xEnemy.getAttribute("up"), up);
        getFloat(xEnemy.getAttribute("down"), down);
        getFloat(xEnemy.getAttribute("movedirection"), moveDirection);
        getFloat(xEnemy.getAttribute("viewdistance"), viewDistance);
        eCreator.createMovingEnemy(sf::Vector2f( x * scale + 25, y * scale + 25), x*scale - left*scale, x*scale + right*scale, y*scale-up*scale, y*scale+ down*scale, moveDirection, viewDirection, viewAngle, viewDistance, sprite_file_name);
      }
      else {
        float rotateAngle;
        getFloat(xEnemy.getAttribute("rotateangle"), rotateAngle);
        eCreator.createStaticEnemy(sf::Vector2f( x * scale + 25, y * scale + 25), viewDirection, viewAngle, viewDistance, rotateAngle, sprite_file_name);
      }
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
