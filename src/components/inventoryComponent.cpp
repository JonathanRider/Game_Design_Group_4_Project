#include "components/inventoryComponent.h"

InventoryComponent::InventoryComponent(GraphicsComponent *gp): gComponent(gp)
{
  this->setType(constants::INVENTORY);
  current_index = -1;
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
  if (gComponent == NULL)
    return;
}
void InventoryComponent::draw(){
  
}
