#ifndef PENCIL_H
#define PENCIL_H

#include <string>
#include <SFML/Graphics.hpp>

#include "Tool.h"

class Pencil : public Tool {
  public:
  Pencil(std::string name);
  ~Pencil();
  void draw(sf::RenderTexture& renderTexture, sf::Vector2f cursorCoords, sf::Color color) override;

};

#endif