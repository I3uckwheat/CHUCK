#pragma once
#include "SceneDirector.h"

class SceneDirector;

class Scene {
public:
  virtual void init() =0;
  virtual void update(SceneDirector* sceneDirector) =0;
  virtual void draw() =0;
  virtual void uninit() =0;
};
