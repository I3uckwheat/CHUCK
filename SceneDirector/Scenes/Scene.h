#pragma once
#include "SceneDirector.h"
#include "Ui.h"
#include <stack>
#include <vector>

class SceneDirector;
class Ui;

class Scene {
public:
  virtual ~Scene() {};
  std::vector<std::unique_ptr<Ui>> uiStack;
  virtual void init() =0;
  virtual void update(SceneDirector* sceneDirector) =0;
  virtual void draw() =0;
  virtual void uninit() =0;
};
