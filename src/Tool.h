#ifndef TOOL_H
#define TOOL_H

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>

class Tool {
  public:
  Tool(std::string pName);
  Tool();
  virtual ~Tool();
  //virtual void draw(sf::RenderWindow& window, sf::Vector2f cursorCoords, sf::Color color) = 0;
  virtual void draw(sf::RenderTexture& renderTexture, sf::Vector2f cursorCoords, sf::Color color) = 0;
  virtual std::string getName();

  protected:
  std::string name;

};

#endif