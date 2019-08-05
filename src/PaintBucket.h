#ifndef PAINT_BUCKET_H
#define PAINT_BUCKET_H

#include <string>
#include <vector>
#include <forward_list>
#include <list>
#include <SFML/Graphics.hpp>

#include "Tool.h"

class PaintBucket : public Tool {
  public:
  PaintBucket(std::string name);
  ~PaintBucket();
  void mouseDown(sf::RenderTexture& renderTexture, sf::Vector2f cursorCoords, sf::Color color) override;
  void mouseUp(sf::RenderTexture& renderTexture, sf::Vector2f cursorCoords, sf::Color color) override;

  private:
  void changePixels(int x, int y, sf::Image* image, sf::Color selectedColor);
};

#endif