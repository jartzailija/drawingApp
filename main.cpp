#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "src/Canvas.h"
#include "src/Pencil.h"
#include "src/ToolBar.h"
#include "src/State.h"

const int width = 1280;
const int height = 800;
const int toolbarHeight = 50;
const sf::Vector2i canvasDimensions = sf::Vector2i(width, height - toolbarHeight);
const std::string fileName = "image.png";

int main() {
  sf::RenderWindow window({width, height}, "Window", sf::Style::Close);
  ToolBar toolbar(window, width, toolbarHeight);
  std::vector<sf::Vertex> lineCoords;
  sf::Color lineColor = sf::Color::Black;
  Canvas canvas(window, canvasDimensions, toolbarHeight, toolbar);

  canvas.loadImage(fileName);

  while (window.isOpen()) {
    sf::Event event;
    canvas.checkStatus();
    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) {
        window.close();
      }
      if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        sf::Vector2f mousePosition = (sf::Vector2f)sf::Mouse::getPosition(window);
        if(canvas.isInsideborders(mousePosition)) {
          canvas.tellMouseCoords(mousePosition);
        }
        else {
          canvas.save(fileName);
        }
      }

      toolbar.handleEvent(event);
    }

    window.clear(sf::Color(255, 255, 255));
    toolbar.render();
    canvas.render();
    window.display();
  }
}
