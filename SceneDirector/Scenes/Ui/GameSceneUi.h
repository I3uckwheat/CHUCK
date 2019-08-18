#pragma once

#include "Ui.h"

class GameSceneUi: public Ui {
public:
  void draw() override;
  void update(Scene* scene) override;
};