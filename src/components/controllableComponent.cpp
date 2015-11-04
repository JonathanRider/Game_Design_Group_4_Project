#include "../components/controllableComponent.h"

ControllableComponent::ControllableComponent(bool active, sf::Keyboard::Key up ,
                      sf::Keyboard::Key down,
                      sf::Keyboard::Key left,
                      sf::Keyboard::Key right,
                      sf::Keyboard::Key item,
                      sf::Keyboard::Key use,
                      sf::Keyboard::Key next,
                      sf::Keyboard::Key prev,
                      sf::Keyboard::Key pause)
:isActive(active), upKey(up), downKey(down), leftKey(left), rightKey(right), useKey(use), itemKey(item), nextItemKey(next), prevItemKey(prev), pauseKey(pause)
{
  this->setType(constants::CONTROLLABLE);
}


void ControllableComponent::changeKey(constants::Input i, sf::Keyboard::Key newKey){
  switch(i){
    case constants::UP: upKey = newKey; break;
    case constants::DOWN: downKey = newKey; break;
    case constants::LEFT: leftKey = newKey; break;
    case constants::RIGHT: rightKey = newKey; break;
    case constants::ITEM: itemKey = newKey; break;
    case constants::USE: useKey = newKey; break;
    case constants::NEXTITEM: nextItemKey = newKey; break;
    case constants::PREVITEM: prevItemKey = newKey; break;
    case constants::PAUSE: prevItemKey = newKey; break;
  }


}

sf::Keyboard::Key ControllableComponent::getKey(constants::Input i){
  switch(i){
    case constants::UP: return upKey;
    case constants::DOWN: return downKey;
    case constants::LEFT: return leftKey;
    case constants::RIGHT: return rightKey;
    case constants::ITEM: return itemKey;
    case constants::USE: return useKey;
    case constants::NEXTITEM: return nextItemKey;
    case constants::PREVITEM: return prevItemKey;
    case constants::PAUSE: return pauseKey;
  }
}
