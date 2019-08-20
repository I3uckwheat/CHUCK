#pragma once

#include "Scene.h"
#include <memory>
#include <vector>

class Scene;

class Ui {
public:
  virtual ~Ui() {}
  virtual bool hasKeyboardControl() { return true; }
  virtual bool hasMouseControl() { return true; }
  virtual void update(std::vector<std::unique_ptr<Ui>>& uiLayers) =0;
  virtual void draw() =0;
};