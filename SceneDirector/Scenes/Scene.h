#pragma once

#include "SceneDirector.h"
#include "TiledMap.h"
#include "raylib.h"
#include "Ui.h"
#include <stack>

class SceneDirector;

class Scene {
public:
  std::stack<Ui> uiStack;
  virtual void init() =0;
  virtual void update(SceneDirector* sceneDirector) =0;
  virtual void draw() =0;
  virtual void uninit() =0;
};
