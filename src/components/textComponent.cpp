#include "components/textComponent.h"

TextComponent::TextComponent(std::list<sf::Sprite*> tl, float a, float al)
  :textList(tl), angle(a), alpha(al)
{
  this->setType(constants::TEXT);
  listCount = 0;
  maxCount = tl.size();
}
