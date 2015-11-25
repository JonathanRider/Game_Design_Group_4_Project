#ifndef _INVENTORY_COMPONENT_H_
#define _INVENTORY_COMPONENT_H_

#include "components/component.h"
#include "components/graphicsComponent.h"
#include <vector>

class InventoryComponent : public Component
{
public:
  InventoryComponent(GraphicsComponent *gp);
  ~InventoryComponent();

  enum InventoryItem { INV_BULLET_SMOKE, /*add inventory item before here */ INV_MAX };
  void addItem(InventoryItem item, int number);
  void nextItem();
  void prevItem();
//  void getCurrent();
  bool consume();//consume the current item pointed by current_index; return false if the number of the item is already 0;

  void updateGraphics();
  void draw();

private:
  class InventoryStruct {
  public:
    InventoryStruct(InventoryItem i, int n):item(i),number(n){}
    InventoryItem item;
    int number;
  };

  GraphicsComponent * gComponent;
  std::vector<InventoryStruct> inventory_list;
  int current_index;
};


#endif
