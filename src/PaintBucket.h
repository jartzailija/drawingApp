#ifndef PAINT_BUCKET_H
#define PAINT_BUCKET_H

#include <string>
#include <SFML/Graphics.hpp>

#include "Tool.h"

class PaintBucket : public Tool {
  public:
  PaintBucket();
  virtual ~PaintBucket();
  virtual void draw(sf::RenderWindow& window, sf::Vector2f cursorCoords, sf::Color color);

  private:
  //std::string name;

};

#endif