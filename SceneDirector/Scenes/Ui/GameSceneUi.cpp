#include "GameSceneUi.h"
#include "raylib.h"

#include <memory>

void GameSceneUi::update(std::vector<std::unique_ptr<Ui>>& uiLayers) {
  if(IsKeyPressed(KEY_I)) {
    uiLayers.emplace_back(std::make_unique<Inventory>());   
  }
}

void GameSceneUi::draw() {
  DrawText("GameSceneUi, Press 'I' to open inventory", 33, 33, 22, BLUE);
}

bool GameSceneUi::hasKeyboardControl() { return false; }
bool GameSceneUi::hasMouseControl() { return false; }


void Inventory::update(std::vector<std::unique_ptr<Ui>>& uiLayers) {
  if(IsKeyPressed(KEY_I)) {
    uiLayers.pop_back();   
  }
}

void Inventory::draw() {
  DrawText("GameInventory, Press 'I' to close inventory", 73, 133, 22, GREEN);
}
