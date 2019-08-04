#include "ToolBar.h"

ToolBar::ToolBar(sf::RenderWindow& pWindow, int pWidth, int pToolbarHeight)
: window(pWindow), gui(pWindow) {
  toolbarHeight = pToolbarHeight;
  width = pWidth;
  initTools();
  selectedTool = tools[0];
  std::cout << "pencil " << selectedTool->getName() << std::endl;

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

Tool& ToolBar::getSelectedTool() {
  return *selectedTool;
}


ToolBar::~ToolBar() {
  for (auto it = tools.begin(); it != tools.end(); it++) {
    delete (*it);
  }
}

void ToolBar::initTools() {
  Pencil* pencil = new Pencil("Pencil");
  PaintBucket* paintBucket = new PaintBucket("PaintBucket");
  tools.push_back(pencil);
  tools.push_back(paintBucket);
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
    auto button = tgui::Button::create((*itr)->getName());
    button->setSize(50, 20);
    button->setPosition((i + 1) * 50, 0);
    button->connect("pressed", [=](){selectTool(*itr);});
    panel->add(button);
    i++;
  }
  gui.add(panel);
}