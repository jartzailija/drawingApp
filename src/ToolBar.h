#ifndef TOOLBAR_H
#define TOOLBAR_H

#include <string>
#include <iostream>
#include <TGUI/TGUI.hpp>
#include <TGUI/Widgets/Panel.hpp>

#include "Tool.h"
#include "Pencil.h"
#include "PaintBucket.h"

class ToolBar {
  public:
  ToolBar(sf::RenderWindow& window, int width, int toolbarHeight);
  ~ToolBar();
  Tool* getSelectedTool();
  void render();
  void handleEvent(sf::Event event);

  private:
  void initTools();
  void loadWidgets(tgui::Gui& gui);
  void selectTool(Tool* tool);

  Tool* selectedTool;
  std::map<std::string, Tool*> tools;
  int toolbarHeight;
  int width;
  sf::RenderWindow& window;
  tgui::Gui gui;
};

#endif