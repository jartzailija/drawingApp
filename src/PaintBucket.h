#ifndef PAINT_BUCKET_H
#define PAINT_BUCKET_H

#include <string>
#include <SFML/Graphics.hpp>

#include "Tool.h"

class PaintBucket : public Tool {
  public:
  PaintBucket(std::string name);
  ~PaintBucket();
  void draw(sf::RenderTexture& renderTexture, sf::Vector2f cursorCoords, sf::Color color) override;

};

#endif