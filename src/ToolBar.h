#ifndef TOOLBAR_H
#define TOOLBAR_H

//#include <string>
#include <iostream>
#include <vector>
#include <TGUI/TGUI.hpp>
#include <TGUI/Widgets/Panel.hpp>

#include "Tool.h"
#include "Pencil.h"
#include "PaintBucket.h"

class ToolBar {
  public:
  ToolBar(sf::RenderWindow& window, int width, int toolbarHeight);
  ~ToolBar();
  Tool& getSelectedTool();
  void render();
  void handleEvent(sf::Event event);
  bool isSomeModalOpen();
  sf::Color getSelectedColor();

  private:
  void initTools();
  void loadWidgets(tgui::Gui& gui);
  void selectTool(Tool* tool);
  void loadTools(tgui::Gui& gui, std::shared_ptr<tgui::Panel> panel);
  void loadOtherButtons(tgui::Gui& gui, std::shared_ptr<tgui::Panel> panel);
  void loadColorSelector(tgui::Gui& gui);
  void setColor(tgui::Color);
  std::shared_ptr<tgui::Button> createColorButton(tgui::Gui& gui, int x, int y, tgui::Color color);

  Tool* selectedTool;
  std::vector<Tool*> tools;
  int toolbarHeight;
  int width;
  sf::RenderWindow& window;
  tgui::Gui gui;
  std::shared_ptr<tgui::ChildWindow> colorModal;
  bool someModalOpen;
  sf::Color selectedColor;
};

#endif