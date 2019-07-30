#ifndef STATE_H
#define STATE_H

#include <string>
#include <iostream>
#include <TGUI/TGUI.hpp>
#include <TGUI/Widgets/Panel.hpp>

#include "Tool.h"
#include "Pencil.h"

//TODO: Jatka tämän tekoa

class State {
  public:
  State();
  ~State();
  void setTool(std::string toolName);
  /*Tool* getSelectedTool();
  //static void selectTool(Tool* tool);
  static void selectTool(std::string tool);

  //static Tool* selectedTool;
  static std::string selectedTool;*/

  private:
  std::string toolName;
  /*void initTools();
  void loadWidgets(tgui::Gui& gui);

  std::map<std::string, Tool*> tools;
  int toolbarHeight;
  int width;
  sf::RenderWindow& window;*/
};

#endif