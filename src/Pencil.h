#ifndef PENCIL_H
#define PENCIL_H

#include <string>
#include <SFML/Graphics.hpp>

#include "Tool.h"

class Pencil : public Tool {
  public:
  Pencil(std::string name);
  ~Pencil();
  void mouseDown(sf::RenderTexture& renderTexture, sf::Vector2f cursorCoords, sf::Color color) override;
  void mouseUp(sf::RenderTexture& renderTexture, sf::Vector2f cursorCoords, sf::Color color) override;

  private:
  std::vector<sf::Vertex> lineCoords;

};

#endif