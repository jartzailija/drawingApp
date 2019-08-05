#include "Pencil.h"

Pencil::Pencil(std::string pName) : Tool(pName) {
}

Pencil::~Pencil() {
}

void Pencil::mouseDown(sf::RenderTexture& renderTexture, sf::Vector2f cursorCoords, sf::Color color) {
  lineCoords.push_back(sf::Vertex(cursorCoords, color));
  if(lineCoords.size() > 1) {
    lineCoords.push_back(sf::Vertex(cursorCoords, color));
  }

  if(lineCoords.size() > 0) {
    renderTexture.draw(&lineCoords[0], lineCoords.size(), sf::Lines);
  }
}

void Pencil::mouseUp(sf::RenderTexture& renderTexture, sf::Vector2f cursorCoords, sf::Color color) {
  lineCoords.clear();
}