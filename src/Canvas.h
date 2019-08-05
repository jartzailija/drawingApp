#ifndef CANVAS_H
#define CANVAS_H

#include <string>
#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "coordinates.h"
#include "Tool.h"
#include "ToolBar.h"

class Canvas {
  public:
  Canvas(sf::RenderWindow& window, sf::Vector2<int> textureDimensions, int upperLimit, ToolBar& toolbar);
  ~Canvas();
  Coordinates getCoords();
  void save(std::string filename);
  void tellMouseCoords(sf::Vector2f cursorCoords);
  bool isInsideborders(sf::Vector2f cursorCoords) const;
  void render();
  bool loadImage(std::string filename);

  private:
  Coordinates calculateCoords(sf::Vector2i textureDimensions, int upperLimit) const;
  void preRender();
  void attachChanges();
  void checkIfNeededToAttach();

  sf::RenderWindow& window;
  sf::Vector2i textureDimensions;
  Coordinates coords; 
  int upperLimit;
  std::vector<sf::Vertex> lineCoords;
  sf::RenderTexture canvasTexture;
  ToolBar& toolbar;
  bool wasMousePreviouslyPressed;
};

#endif