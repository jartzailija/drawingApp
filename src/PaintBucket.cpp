#include "PaintBucket.h"

PaintBucket::PaintBucket(std::string name) : Tool(name) {
}

PaintBucket::~PaintBucket() {
}

void PaintBucket::draw(sf::RenderTexture& canvasTexture, sf::Vector2f cursorCoords, sf::Color selectedColor) {
  sf::Image image = canvasTexture.getTexture().copyToImage();
  sf::Color color = image.getPixel(cursorCoords.x, cursorCoords.y);
  std::cout << "Väri " << color.toInteger() << std::endl;
}