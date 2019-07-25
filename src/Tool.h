#ifndef TOOL_H
#define TOOL_H

#include <string>
#include <SFML/Graphics.hpp>

class Tool {
  public:
  Tool(std::string name);
  virtual ~Tool();
  virtual void draw(sf::RenderWindow& window, sf::Vector2f cursorCoords, sf::Color color);

  protected:
  std::string name;

};

#endif