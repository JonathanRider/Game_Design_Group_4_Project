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
  this->setType(CONTROLLABLE);
}


void ControllableComponent::changeKey(Input i, sf::Keyboard::Key newKey){
  switch(i){
    case UP: upKey = newKey; break;
    case DOWN: downKey = newKey; break;
    case LEFT: leftKey = newKey; break;
    case RIGHT: rightKey = newKey; break;
    case ITEM: itemKey = newKey; break;
    case USE: useKey = newKey; break;
    case NEXTITEM: nextItemKey = newKey; break;
    case PREVITEM: prevItemKey = newKey; break;
    case PAUSE: prevItemKey = newKey; break;
  }


}

sf::Keyboard::Key ControllableComponent::getKey(Input i){
  switch(i){
    case UP: return upKey;
    case DOWN: return downKey;
    case LEFT: return leftKey;
    case RIGHT: return rightKey;
    case ITEM: return itemKey;
    case USE: return useKey;
    case NEXTITEM: return nextItemKey;
    case PREVITEM: return prevItemKey;
    case PAUSE: return pauseKey;
  }
}
