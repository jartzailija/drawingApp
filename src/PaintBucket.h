#ifndef PAINT_BUCKET_H
#define PAINT_BUCKET_H

#include <string>
#include <vector>
#include <tuple>
#include <SFML/Graphics.hpp>

#include "Tool.h"

class PaintBucket : public Tool {
  public:
  PaintBucket(std::string name);
  ~PaintBucket();
  void draw(sf::RenderTexture& renderTexture, sf::Vector2f cursorCoords, sf::Color color) override;

  private:
  void changePixelColorRecursively(int x, int y, sf::Image* image, sf::Color* selectedColor, uint maxX, uint maxY);

  std::vector<std::tuple<int, int>> editedPixels;
};

#endif