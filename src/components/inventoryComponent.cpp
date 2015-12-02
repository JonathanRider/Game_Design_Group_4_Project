#include "components/inventoryComponent.h"
#include "global.h"
#include "typeConversion.h"
#include <iostream>
#include <cmath>

namespace{
  std::string int2string(int i){ //always return two digits
    char tmp_string[3];
    tmp_string[2] = '\0';
    tmp_string[1] = i % 10 + 48;
    tmp_string[0] = i / 10 + 48;
    std::string ret_str = tmp_string;
    return ret_str;
  }
}
InventoryComponent::InventoryComponent():b_timingAlert(false){
  this->setType(constants::INVENTORY);
  current_index = -1;
  texture_name_list.resize(INV_MAX);

  texture_name_list[INV_BULLET_COMMON]="resources/graphics/sprite/gunIcon.png";
  texture_name_list[INV_BULLET_SMOKE]="resources/graphics/sprite/grenadeIcon.png";

  box_display.setSize(sf::Vector2f(100, 80));
  box_display.setFillColor(sf::Color(255,255,255,200));
//  box_display.setOutlineColor(sf::Color::Red);
//  box_display.setOutlineThickness(5);


  number_display.setFont(*(global()->gameEngine.resourceManager->getFont("resources/font/6809 chargen.ttf")));
  number_display.setCharacterSize(24);
  number_display.setColor(sf::Color::Red);
  //number_display.setStyle(sf::Text::Bold | sf::Text::Underlined);

  level_sign.setFont(*(global()->gameEngine.resourceManager->getFont("resources/font/6809 chargen.ttf")));
  level_sign.setCharacterSize(50);
  level_sign.setColor(sf::Color(0,0,0,250));

  timer_display.setFont(*(global()->gameEngine.resourceManager->getFont("resources/font/6809 chargen.ttf")));
  timer_display.setCharacterSize(50);
  timer_display.setColor(sf::Color(153,153,0,250));
  timer.setStartTime(5);
}

InventoryComponent::~InventoryComponent(){}

void InventoryComponent::addItem(InventoryItem item, int number){
  if (number < 0 ||  item < 0 || item >= INV_MAX )
    return;
  for(int i=0; i < inventory_list.size(); i++){
    if (inventory_list[i].item == item){
      inventory_list[i].number = number;
      return;
    }
  }
  current_index = 0;
  inventory_list.push_back(InventoryStruct(item,number));
}

void InventoryComponent::nextItem(){
  if (current_index >= 0) {
    if (current_index == inventory_list.size() - 1 ) {
      current_index = 0;
    } else{
      current_index ++;
    }
  }
}
void InventoryComponent::prevItem(){
  if (current_index >= 0) {
    if (current_index == 0 ) {
      current_index = inventory_list.size() - 1 ;
    } else{
      current_index --;
    }
  }
}
InventoryComponent::InventoryItem InventoryComponent::getCurrent(){
  if (current_index >= 0) {
    return inventory_list[current_index].item;
  }
  else {
    return INV_MAX;
  }
}
bool InventoryComponent::consume() {
  if (current_index >= 0 ) {
    if (inventory_list[current_index].number <= 0) {
      return false;
    }
    inventory_list[current_index].number -= 1;
    return true;
  }
  return false;
}
void InventoryComponent::update(){
  if (ceil(timer.getTime()) <= 0){
    global()->gameEngine.gameState = constants::NONPLAYING;
    global()->gameEngine.nonPlaying->receiveInput(constants::INPUT_LOSE, NULL);
  }
  if (current_index < 0) {
    return;
  }
  inv_sprite.setTexture(*(global()->gameEngine.resourceManager->getTexture(texture_name_list[current_index])));
  number_display.setString(typeconvert::int2string(inventory_list[current_index].number));
  if (timer.getTime() <= 10 && b_timingAlert == false){
    timer_display.setColor(sf::Color(255,0,0,244));
    b_timingAlert = true;
  }
  timer_display.setString(timer.getTimeString());

}
void InventoryComponent::draw(sf::RenderWindow &w, sf::View &v){
  sf::Vector2f center = v.getCenter();
  sf::Vector2f size = v.getSize();
  sf::Vector2f base_point;


  //draw the level number
  level_sign.setPosition(center.x - 340, center.y - 280);
  w.draw(level_sign);
  //draw the timer
  static sf::Clock clock;
  static bool b_timer_disappear = false;
  timer_display.setPosition(center.x + 200, center.y - 280);
  if (b_timingAlert && timer.getTime() > 0){
    if (b_timer_disappear){
      if (clock.getElapsedTime().asSeconds() >= 0.4){
        clock.restart();
        b_timer_disappear = false;
        w.draw(timer_display);
      }
    }
    else {
      if (clock.getElapsedTime().asSeconds() >= 0.6){
        clock.restart();
        b_timer_disappear = true;
      }
      w.draw(timer_display);
    }
  }
  else {
    w.draw(timer_display);
  }

  if (current_index < 0) {
    return;
  }

  base_point.x = center.x - 50;
  base_point.y = center.y + size.y / 2 - 100;



  box_display.setPosition(base_point);
  w.draw(box_display);
  inv_sprite.setPosition(base_point.x + 10, base_point.y + 10);
  w.draw(inv_sprite);
  number_display.setPosition(base_point.x + 55, base_point.y + 20);
  w.draw(number_display);
}
void InventoryComponent::setLevelSign(int level){
  level_sign.setString("Level "+typeconvert::int2string(level));
}
void InventoryComponent::setTimerStartTime(int seconds){
  timer.setStartTime(seconds);
}
InventoryComponent::Timer::Timer(int seconds):start_seconds(seconds){}
InventoryComponent::Timer::Timer():start_seconds(0){}
InventoryComponent::Timer::~Timer(){}
void InventoryComponent::Timer::restart(){
  b_paused = false;
  clock.restart();
  time = sf::Time::Zero;
}
void InventoryComponent::Timer::pause(){
  if (!b_paused){
    b_paused = true;
    time += clock.getElapsedTime();
  }
}
void InventoryComponent::Timer::resume(){
  if (b_paused){
    b_paused = false;
    clock.restart();
  }
}
double InventoryComponent::Timer::getTime(){
  double ret_val = (double)start_seconds - time.asSeconds() - clock.getElapsedTime().asSeconds();
  if (ret_val <= 0){
    pause();
    ret_val = 0;
  }
  return ret_val;
}
std::string InventoryComponent::Timer::getTimeString(){
  int value = ceil(getTime());
  std::string ret_str = int2string(value/60) +":"+ int2string(value%60);
  return ret_str;
}
