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
  //enum InventoryItem { INV_GUNICON, INV_GRENADEICON, /*add inventory item before here */ INV_MAX };
  enum InventoryItem { INV_BULLET_COMMON, INV_BULLET_SMOKE, /*add inventory item before here */ INV_MAX };
  void setLevelSign(int level);
  void addItem(InventoryItem item, int number);
  void nextItem();
  void prevItem();
  InventoryItem getCurrent();
  bool consume();//consume the current item pointed by current_index; return false if the number of the item is already 0;

  void update();
  void draw(sf::RenderWindow &w, sf::View &v);
  void setTimerStartTime(int seconds);
  void pauseTimer();
  void resumeTimer();

private:
  class InventoryStruct {
  public:
    InventoryStruct(InventoryItem i, int n):item(i),number(n){}
    InventoryItem item;
    int number;
  };
  class Timer {
    public:
      Timer();
      Timer(int seconds);
      ~Timer();
      void restart();
      void pause();
      void resume();
      double getTime();//in seconds;
      void setStartTime(int seconds){start_seconds= seconds;}
      std::string getTimeString();
    private:
      int start_seconds;
      sf::Clock clock;
      sf::Time time;
      bool b_paused;
  };
  Timer timer;
  std::vector<InventoryStruct> inventory_list;
  int current_index;
  std::vector<std::string> texture_name_list;
  sf::Sprite inv_sprite;
  sf::RectangleShape box_display, timer_box;
  sf::Text number_display, level_sign, timer_display;
  bool b_timingAlert;
};


#endif
