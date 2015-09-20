#include <SFML/Graphics.hpp>

int main(int argc, char** argv)
{
  // create main window
  sf::RenderWindow App(sf::VideoMode(800,600,32), "Hello World - SFML");

  sf::RectangleShape shape = sf::RectangleShape(sf::Vector2f(50, 50));
  // start main loop
  while(App.isOpen())
  {
    // process events
    sf::Event Event;
    while(App.pollEvent(Event))
    {

      // Exit
      if(Event.type == sf::Event::Closed)
        App.close();
    }

    // clear screen and fill with blue
    App.clear(sf::Color::Blue);
    App.draw(shape);

    // display
    App.display();
  }

  // Done.
  return 0;
}
