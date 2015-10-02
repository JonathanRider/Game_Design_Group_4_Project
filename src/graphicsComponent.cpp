#include "graphicsComponent.h"
#include <iostream>

graphicsComponent::graphicsComponent(/*sf::Sprite*/ sf::RectangleShape* s, float a, float al)
  :sprite(s), angle(a), alpha(al)
{
}

void graphicsComponent::draw(sf::RenderWindow *w, sf::Vector2f xy){
  std::cout << "before pos\n";
  //sprite->setPosition(xy);

sf::RectangleShape shape = sf::RectangleShape(sf::Vector2f(50, 50));
std::cout << "before thickness\n";
std::cout << sprite->getOutlineThickness() << std::endl;
std::cout << "test\n";


  w->draw(*sprite);


}
