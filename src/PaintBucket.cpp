#include "PaintBucket.h"

PaintBucket::PaintBucket(std::string name) : Tool(name) {
}

PaintBucket::~PaintBucket() {
}

void PaintBucket::mouseDown(sf::RenderTexture& canvasTexture, sf::Vector2f cursorCoords, sf::Color selectedColor) {
  sf::Image image = canvasTexture.getTexture().copyToImage();
  sf::Color oldColor = image.getPixel(cursorCoords.x, cursorCoords.y);
  changePixels(cursorCoords.x, cursorCoords.y, &image, selectedColor);
  sf::Texture tmpTexture;
  if(!tmpTexture.loadFromImage(image)) {
    //return false;
  }
  sf::Sprite sprite(tmpTexture);
  canvasTexture.draw(sprite);

}

void PaintBucket::mouseUp(sf::RenderTexture& canvasTexture, sf::Vector2f cursorCoords, sf::Color selectedColor) {
}

void PaintBucket::changePixels(int x, int y, sf::Image* image, sf::Color selectedColor) {
  sf::Color oldColor = image->getPixel(x, y);
  if(selectedColor != oldColor) {
    int maxX = (int)image->getSize().x - 1;
    int maxY = (int)image->getSize().y - 1;
    
    std::list<std::pair<int, int>> pixelsToCheck = {std::make_pair(x, y)};
    auto it = pixelsToCheck.begin();
    
    while(it != pixelsToCheck.end()) {
      if(it->first >= 0 && it->second >= 0 && it->first <= maxX && it->second <= maxY) {
        if(image->getPixel(it->first, it->second) == oldColor) {
          image->setPixel(it->first, it->second, selectedColor);
          
          pixelsToCheck.emplace_back(it->first - 1, it->second);
          pixelsToCheck.emplace_back(it->first + 1, it->second);
          pixelsToCheck.emplace_back(it->first, it->second - 1);
          pixelsToCheck.emplace_back(it->first, it->second + 1);
        }
      }
      it++;
    }
  }
}
