#include "PaintBucket.h"

PaintBucket::PaintBucket(std::string name) : Tool(name) {
}

PaintBucket::~PaintBucket() {
}

void PaintBucket::draw(sf::RenderTexture& canvasTexture, sf::Vector2f cursorCoords, sf::Color selectedColor) {
  sf::Image image = canvasTexture.getTexture().copyToImage();
  sf::Color oldColor = image.getPixel(cursorCoords.x, cursorCoords.y);
  if(selectedColor != oldColor) {
    uint maxX = (uint)image.getSize().x - 1;
    uint maxY = (uint)image.getSize().y - 1;
    changePixelColorRecursively((int)cursorCoords.x, (int)cursorCoords.y, &image, &selectedColor, maxX, maxY);
    
    sf::Texture tmpTexture;
    if(!tmpTexture.loadFromImage(image)) {
      //return false;
    }
    sf::Sprite sprite(tmpTexture);
    canvasTexture.draw(sprite);
  }

}

//TODO: tsekkaa ettei mee imagen ulkopuolelle
void PaintBucket::changePixelColorRecursively(int x, int y, sf::Image* image, sf::Color* selectedColor, uint maxX, uint maxY) {
  if(x >= 0 && y >= 0 && x <= maxX && y <= maxY) {
    if(image->getPixel(x, y) != *selectedColor) {
      image->setPixel(x, y, *selectedColor);
      changePixelColorRecursively(x - 1, y, image, selectedColor, maxX, maxY);
      changePixelColorRecursively(x + 1, y, image, selectedColor, maxX, maxY);
      changePixelColorRecursively(x, y - 1, image, selectedColor, maxX, maxY);
      changePixelColorRecursively(x, y + 1, image, selectedColor, maxX, maxY);
      //std::cout << "Väri " << std::endl;
    }
  }
}
