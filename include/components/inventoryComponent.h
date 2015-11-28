#ifndef _INVENTORY_COMPONENT_H_
#define _INVENTORY_COMPONENT_H_

#include "components/component.h"
#include <vector>
#include <SFML/Graphics.hpp>

class InventoryComponent : public Component
{
public:
  InventoryComponent();
  ~InventoryComponent();

  enum InventoryItem { INV_GUNICON, INV_GRENADEICON, /*add inventory item before here */ INV_MAX };
  void addItem(InventoryItem item, int number);
  void nextItem();
  void prevItem();
//  void getCurrent();
  bool consume();//consume the current item pointed by current_index; return false if the number of the item is already 0;

  void updateGraphics();
  void draw(sf::RenderWindow &w, sf::View &v);

private:
  class InventoryStruct {
  public:
    InventoryStruct(InventoryItem i, int n):item(i),number(n){}
    InventoryItem item;
    int number;
  };

  std::vector<InventoryStruct> inventory_list;
  int current_index;

  std::vector<std::string> texture_name_list;
  sf::Sprite inv_sprite;
  sf::RectangleShape box_display;
  sf::Text number_display;
};


#endif
