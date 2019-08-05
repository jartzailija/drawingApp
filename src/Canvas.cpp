#include "Canvas.h"

Canvas::Canvas(sf::RenderWindow& pWindow, sf::Vector2<int> pTextureDimensions, int pUpperLimit, ToolBar& pToolbar)
  : window(pWindow), toolbar(pToolbar) {
  textureDimensions = pTextureDimensions;
  upperLimit = pUpperLimit;
  coords = calculateCoords(pTextureDimensions, pUpperLimit);
  selectedColor = sf::Color::Green;
  selectedToolName = toolbar.getSelectedTool().getName();
  wasMousePreviouslyPressed = false;
  //TODO: add try-catch
  if(!canvasTexture.create(textureDimensions.x, textureDimensions.y)) {
    std::cout << "Victor Mike" << std::endl;
  }

  canvasTexture.clear(sf::Color::White);
}

Canvas::~Canvas() {
}

void Canvas::save(std::string fileName) {
  sf::Texture texture = canvasTexture.getTexture();
  sf::Image image = texture.copyToImage();
  image.saveToFile(fileName);
}

bool Canvas::loadImage(std::string fileName) {
  sf::Texture tmpTexture;
  if(!tmpTexture.loadFromFile(fileName)) {
    return false;
  }
  sf::Sprite sprite(tmpTexture);
  canvasTexture.draw(sprite);
  return true;
}

bool Canvas::isInsideborders(sf::Vector2f cursorCoords) const {
  if(!coords.valid) {
    return false;
  }

  bool isInside = true;
  if(cursorCoords.y <= coords.top || cursorCoords.y >= coords.bottom) {
    isInside = false;
  }

  if(cursorCoords.x <= coords.left || cursorCoords.x >= coords.right) {
    isInside = false;
  }

  return isInside;
}

void Canvas::tellMouseCoords(sf::Vector2f cursorCoords) {
  sf::Vector2f transformedCoords(cursorCoords.x - coords.left, cursorCoords.y - coords.top);
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
    toolbar.getSelectedTool().mouseDown(canvasTexture, transformedCoords, selectedColor);
    wasMousePreviouslyPressed = true;
  }
  else {
    if(wasMousePreviouslyPressed) {
      toolbar.getSelectedTool().mouseUp(canvasTexture, transformedCoords, selectedColor);
    }
    wasMousePreviouslyPressed = false;
  }
}

void Canvas::render() {
  canvasTexture.display();
  sf::Sprite sprite(canvasTexture.getTexture());
  sprite.setOrigin(coords.left, -coords.top);
  window.draw(sprite);
}

//TODO: tsekkaa ylärajan toimivuus, ettei mee toolbarin kaa päällekkäin
Coordinates Canvas::calculateCoords(sf::Vector2i textureDimensions, int upperLimit) const {
  struct Coordinates coords;
  coords.top = upperLimit;
  coords.bottom = upperLimit + textureDimensions.y;
  coords.left = 0;
  coords.right = textureDimensions.x;
  coords.valid = true;
  return coords;
}

Coordinates Canvas::getCoords() {
  return coords;
}