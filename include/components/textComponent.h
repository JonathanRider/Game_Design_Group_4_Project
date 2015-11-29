#ifndef _TEXT_COMPONENT_H_
#define _TEXT_COMPONENT_H_

#include "components/component.h"
#include <SFML/Graphics.hpp>

class TextComponent : public Component
{
public:
  TextComponent(std::vector<sf::Sprite*> tl, float a = 0, float al = 0);
  ~TextComponent(){};

  void addGraphic(sf::Sprite);
  void setRotation(float a);
  void rotate(float a);
  float getRotation();
  void setOpacity(float a);
  int getListCount(){return listCount;}
  int getMaxCount(){return  maxCount;}
  void nextGraphic(){listCount+=1;}

  std::vector<sf::Sprite*> getTextList(){return textList;}

private:
  std::vector<sf::Sprite*> textList;
  int listCount;
  int maxCount;
  float angle;
  float alpha;

};


#endif
