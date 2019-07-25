#ifndef PENCIL_H
#define PENCIL_H

#include <string>
#include <SFML/Graphics.hpp>

#include "Tool.h"

class Pencil : public Tool {
  public:
  //Pencil(std::string name);
  virtual ~Pencil();
  virtual void draw(sf::RenderWindow& window, sf::Vector2f cursorCoords, sf::Color color);

  private:
  //std::string name;

};

#endif