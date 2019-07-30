#include "ToolBar.h"

ToolBar::ToolBar(sf::RenderWindow& pWindow, int pWidth, int pToolbarHeight)
: window(pWindow), gui(pWindow) {
  toolbarHeight = pToolbarHeight;
  width = pWidth;
  initTools();
  selectedTool = tools["Pencil"];

  tgui::Theme theme{"src/themes/default.txt"};
  tgui::Theme::setDefault(&theme);
  try {
    loadWidgets(gui);
  }
  catch (const tgui::Exception& e) {
    std::cerr << "Failed to load TGUI widgets: " << e.what() << std::endl;
    //return 1;
  }
}

ToolBar::~ToolBar() {
  for (auto it = tools.begin(); it != tools.end(); it++) {
    delete it->second;
  }
}

Tool* ToolBar::getSelectedTool() {
  return selectedTool;
}

void ToolBar::initTools() {
  Pencil pencil;
  Pencil pencil2;
  tools.emplace("Pencil", &pencil);
  tools.emplace("Pencil2", &pencil2);
}

void ToolBar::render() {
  gui.draw();
}

void ToolBar::handleEvent(sf::Event event) {
   gui.handleEvent(event);
}

void ToolBar::selectTool(Tool* tool) {
  selectedTool = tool;
}

void ToolBar::loadWidgets(tgui::Gui& gui) {
  auto panel = tgui::Panel::create();
  panel->setPosition(0, 0);
  panel->setSize(width, toolbarHeight);

  int i = 0;
  for (auto itr = tools.begin(); itr != tools.end(); itr++) { 
    auto button = tgui::Button::create(itr->first);
    button->setSize(50, 20);
    button->setPosition((i + 1) * 50, 0);
    button->connect("pressed", [=](Tool* tool){selectTool(tool);}, itr->second);
    panel->add(button);
    i++;
  }
  gui.add(panel);
}