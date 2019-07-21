#ifndef CANVAS_H
#define CANVAS_H

#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "coordinates.h"

class Canvas {
  public:
  Canvas(sf::RenderWindow& window, sf::Vector2<int> textureDimensions, int upperLimit);
  ~Canvas();
  Coordinates getCoords();
  void save(std::string filename);
  void tellMouseCoords(sf::Vector2f cursorCoords);
  bool isInsideborders(sf::Vector2f cursorCoords);
  void render();

  private:
  Coordinates calculateCoords(sf::Vector2i textureDimensions, int upperLimit);
  void preRender();

  sf::RenderWindow& window;
  sf::Vector2i textureDimensions;
  Coordinates coords; 
  int upperLimit;
  sf::Color selectedColor;
  //TODO: tsekkaa pitääkö käsitellä destructorissa
  std::vector<sf::Vertex> lineCoords;
  sf::RenderTexture canvasTexture;
};

#endif