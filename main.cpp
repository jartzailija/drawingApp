#include <TGUI/TGUI.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

int main()
{
  sf::RenderWindow window{{800, 600}, "Window"};
  tgui::Gui gui{window}; // Create the gui and attach it to the window
  std::vector<sf::Vertex> lineCoords;
  sf::Color lineColor = sf::Color::Black;

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2f localPosition = (sf::Vector2f)sf::Mouse::getPosition(window);
        lineCoords.push_back(sf::Vertex(localPosition, lineColor));
        if(lineCoords.size() > 1) {
          lineCoords.push_back(sf::Vertex(localPosition, lineColor));
        }
      }

      gui.handleEvent(event); // Pass the event to the widgets
    }

    window.clear(sf::Color(255, 255, 255));
    gui.draw(); // Draw all widgets
    if(lineCoords.size() > 0) {
      window.draw(&lineCoords[0], lineCoords.size(), sf::Lines);
    }
    window.display();
    //std::cout << "Jeejee" << std::endl;
  }
}
