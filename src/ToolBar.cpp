#include "ToolBar.h"

ToolBar::ToolBar(sf::RenderWindow& pWindow, int pWidth, int pToolbarHeight)
: window(pWindow), gui(pWindow) {
  toolbarHeight = pToolbarHeight;
  width = pWidth;
  initTools();
  selectedTool = tools[0];
  canvas = nullptr;
  saveName = "image.png";
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

void ToolBar::setCanvas(Canvas* pCanvas) {
  canvas = pCanvas;
}

void ToolBar::setFilename(std::string pSaveName) {
  saveName = pSaveName;
}

void ToolBar::initTools() {
  someModalOpen = false;
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

void ToolBar::loadTools(tgui::Gui& gui, std::shared_ptr<tgui::Panel> panel) {
  int i = 0;
  for (auto itr = tools.begin(); itr != tools.end(); itr++) {
    auto button = tgui::Button::create((*itr)->getName());
    button->setSize(100, 20);
    button->setPosition((i) * 100, 0);
    button->connect("pressed", [=](){selectTool(*itr);});
    panel->add(button);
    i++;
  }
}

void ToolBar::loadOtherButtons(tgui::Gui& gui, std::shared_ptr<tgui::Panel> panel) {
  auto colorButton = tgui::Button::create("Color");
  colorButton->setSize(100, 20);
  colorButton->setPosition(0, 20);
  colorButton->connect("pressed", [=](){
    colorModal->setVisible(true);
    someModalOpen = true;
  });   
  panel->add(colorButton);

  auto saveButton = tgui::Button::create("Save");
  saveButton->setSize(100, 20);
  saveButton->setPosition(100, 20);
  saveButton->connect("pressed", [=](){
    if(canvas != nullptr) {
      canvas->save(saveName);
    }
  });   
  panel->add(saveButton);
}

void ToolBar::loadColorSelector(tgui::Gui& gui) {
  
  colorModal = tgui::ChildWindow::create("Select color", tgui::ChildWindow::TitleButton::None);
  colorModal->setSize(100, 50);
  colorModal->setPosition(200, 0);
  colorModal->setVisible(false);

  auto colorPanel = tgui::Panel::create();
  colorPanel->setPosition(0, 0);
  colorPanel->setSize(100, 50);
  colorPanel->add(createColorButton(gui, 0, 0, tgui::Color::Black));
  colorPanel->add(createColorButton(gui, 1, 0, tgui::Color::White));
  colorPanel->add(createColorButton(gui, 2, 0, tgui::Color::Red));
  colorPanel->add(createColorButton(gui, 3, 0, tgui::Color::Green));
  colorPanel->add(createColorButton(gui, 0, 1, tgui::Color::Blue));
  colorPanel->add(createColorButton(gui, 1, 1, tgui::Color::Yellow));
  colorPanel->add(createColorButton(gui, 2, 1, tgui::Color::Magenta));
  colorPanel->add(createColorButton(gui, 3, 1, tgui::Color::Cyan));

  colorModal->add(colorPanel);
  gui.add(colorModal);
}

std::shared_ptr<tgui::Button> ToolBar::createColorButton(tgui::Gui& gui, int x, int y, tgui::Color color) {
  auto button = tgui::Button::create();
  button->setPosition(x * 25, y * 25);
  button->setSize(25, 25);

  tgui::ButtonRenderer br;
  br.setBackgroundColor(color);
  button->setRenderer(br.getData());
  button->connect("pressed", [=](){
    setColor(color);
    colorModal->setVisible(false);
    someModalOpen = false;
  });

  return button;
}

void ToolBar::loadWidgets(tgui::Gui& gui) {
  auto panel = tgui::Panel::create();
  panel->setPosition(0, 0);
  panel->setSize(width, toolbarHeight);
  loadTools(gui, panel);
  loadOtherButtons(gui, panel);
  gui.add(panel);
  loadColorSelector(gui);
}

bool ToolBar::isSomeModalOpen() {
  return someModalOpen;
}

void ToolBar::setColor(tgui::Color color) {
  selectedColor = color;
}

sf::Color ToolBar::getSelectedColor() {
  return selectedColor;
}