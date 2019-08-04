#include "Canvas.h"

Canvas::Canvas(sf::RenderWindow& pWindow, sf::Vector2<int> pTextureDimensions, int pUpperLimit, ToolBar& pToolbar)
  : window(pWindow), toolbar(pToolbar) {
  textureDimensions = pTextureDimensions;
  upperLimit = pUpperLimit;
  coords = calculateCoords(pTextureDimensions, pUpperLimit);
  selectedColor = sf::Color::Black;
  selectedToolName = toolbar.getSelectedTool().getName();
  //TODO: add try-catch
  if(!canvasTexture.create(textureDimensions.x, textureDimensions.y)) {
    std::cout << "Victor Mike" << std::endl;
  }

  canvasTexture.clear(sf::Color::White);
}

Canvas::~Canvas() {
}

void Canvas::save(std::string fileName) {
  preRender();
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
  std::cout << toolbar.getSelectedTool().getName() << std::endl;
  if(toolbar.getSelectedTool().getName() == "PaintBucket") {
    toolbar.getSelectedTool().draw(canvasTexture, transformedCoords, selectedColor);
  }
  else if(lineCoords.size() > 1) {
    lineCoords.push_back(sf::Vertex(transformedCoords, selectedColor));
    lineCoords.push_back(sf::Vertex(transformedCoords, selectedColor));
  }
}

//TODO: hienosäädä
void Canvas::preRender() {
  if(toolbar.getSelectedTool().getName() == "PaintBucket") {
    //std::cout << "Jeejee" << std::endl;
  }

  if(lineCoords.size() > 0) {
    canvasTexture.draw(&lineCoords[0], lineCoords.size(), sf::Lines);
  }
  canvasTexture.display();
}

//Save changes as a solid part to the canvas 
void Canvas::attachChanges() {
  preRender();
  sf::Texture texture = canvasTexture.getTexture();
  sf::Sprite sprite(texture);
  canvasTexture.draw(sprite);
}

void Canvas::checkStatus() {
  if(selectedToolName != toolbar.getSelectedTool().getName()) {
    selectedToolName = toolbar.getSelectedTool().getName();
    attachChanges();
  }
}

void Canvas::render() {
  preRender();
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