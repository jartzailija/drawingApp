#include "Tool.h"


Tool::Tool(std::string pName) {
  name = pName;
}

Tool::Tool() {
}

Tool::~Tool() {
}

std::string Tool::getName() {
  return name;
}