#include "components/inventoryComponent.h"
#include "global.h"
#include "typeConversion.h"
#include <iostream>
InventoryComponent::InventoryComponent(){
  this->setType(constants::INVENTORY);
  current_index = -1;
  texture_name_list.resize(INV_MAX);

  texture_name_list[INV_BULLET_COMMON]="resources/graphics/sprite/inv_bullet_common.png";
  texture_name_list[INV_BULLET_SMOKE]="resources/graphics/sprite/inv_bullet_smoke.png";

  box_display.setSize(sf::Vector2f(50, 100));
//  box_display.setOutlineColor(sf::Color::Red);
//  box_display.setOutlineThickness(5);


  number_display.setFont(*(global()->gameEngine.resourceManager->getFont("resources/font/6809 chargen.ttf")));
  number_display.setCharacterSize(24);
  number_display.setColor(sf::Color::Red);
  //number_display.setStyle(sf::Text::Bold | sf::Text::Underlined);

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
bool InventoryComponent::consume() {
  if (current_index >= 0 ) {
    if (inventory_list[current_index].number == 0) {
      return false;
    }
    inventory_list[current_index].number --;
    return true;
  }
  return false;
}
void InventoryComponent::updateGraphics(){
  if (current_index < 0) {
    return;
  }
  inv_sprite.setTexture(*(global()->gameEngine.resourceManager->getTexture(texture_name_list[current_index])));
  number_display.setString(typeconvert::int2string(inventory_list[current_index].number));
}
void InventoryComponent::draw(sf::RenderWindow &w, sf::View &v){
  if (current_index < 0) {
    return;
  }
  updateGraphics();
  //  v.
  sf::Vector2f center = v.getCenter();
  sf::Vector2f size = v.getSize();

  sf::Vector2f base_point;
  base_point.x = center.x - 50;
  base_point.y = center.y + size.y / 2 - 100;


  box_display.setPosition(base_point);
  w.draw(box_display);
  inv_sprite.setPosition(base_point.x + 10, base_point.y + 10);
  w.draw(inv_sprite);
  number_display.setPosition(base_point.x + 10, base_point.y + 60);
  w.draw(number_display);
}
