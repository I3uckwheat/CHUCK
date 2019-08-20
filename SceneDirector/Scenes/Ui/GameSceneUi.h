#pragma once

#include "Ui.h"

class GameSceneUi : public Ui {
  void update(std::vector<std::unique_ptr<Ui>>& uiLayers) override;
  void draw() override;
  bool hasKeyboardControl() override;
  bool hasMouseControl() override;
};

class Inventory : public Ui {
  void update(std::vector<std::unique_ptr<Ui>>& uiLayers) override;
  void draw() override;
};