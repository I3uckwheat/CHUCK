#pragma once

#include "SceneDirector.h"
#include "TiledMap.h"
#include "raylib.h"

class SceneDirector;

class Scene {
public:
  virtual void init() =0;
  virtual void update(SceneDirector* director) =0;
  virtual void draw() =0;
  virtual void uninit() =0;
};
