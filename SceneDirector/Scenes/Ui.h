#pragma once

#include "Scene.h"

class Scene;

class Ui {
public:
  virtual void draw();
  virtual void update(Scene* scene);
};