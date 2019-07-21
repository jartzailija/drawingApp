#include <TGUI/TGUI.hpp>
#include <TGUI/Widgets/Panel.hpp>
#include <SFML/Graphics.hpp>

#include <iostream>
#include <vector>

#include "src/Canvas.h"

const int width = 1280;
const int height = 800;
const int toolbarHeight = 50;
const sf::Vector2i canvasDimensions = sf::Vector2i(width, height - toolbarHeight);

void selectPen() {
  std::cout << "Jeejee" << std::endl;
}

void loadWidgets( tgui::Gui& gui ) {
  /* auto button = tgui::Button::create("Pen");
  button->setSize({"50%", "16.67%"});
  button->setPosition({"0%", "0%"});
  //gui.add(button);

  // Call the login function when the button is pressed and pass the edit boxes that we created as parameters
  button->connect("pressed", selectPen);*/

  auto panel = tgui::Panel::create();
  panel->setPosition(0, 0);
  panel->setSize(width, toolbarHeight);
  //panel->setBackgroundColor(sf::Color(200, 200, 200));
  for (unsigned int i = 0; i < 5; i++) {
    //std::cout << i << std::endl;
    auto button = tgui::Button::create("Button");
    button->setSize(50, 20);
    button->setPosition((i + 1) * 50, 0);
    panel->add(button);
  }
  gui.add(panel);
}

void save() {

}

int main() {
  sf::RenderWindow window({width, height}, "Window", sf::Style::Close);
  tgui::Gui gui(window); // Create the gui and attach it to the window
  std::vector<sf::Vertex> lineCoords;
  sf::Color lineColor = sf::Color::Black;
  Canvas canvas(window, canvasDimensions, toolbarHeight);
  tgui::Theme theme{"src/themes/default.txt"};
  tgui::Theme::setDefault(&theme);

  try {
      loadWidgets(gui);
    }
  catch (const tgui::Exception& e) {
      std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
      return 1;
  }

  while (window.isOpen()) {
    sf::Event event;
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
          canvas.save("image.png");
        }
      }

      gui.handleEvent(event); // Pass the event to the widgets
    }

    window.clear(sf::Color(255, 255, 255));
    gui.draw(); // Draw all widgets
    canvas.render();
    window.display();
    //std::cout << "Jeejee" << std::endl;
  }
}
