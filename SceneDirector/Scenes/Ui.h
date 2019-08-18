#pragma once

#include "Scene.h"

class Scene;

class Ui {
public:
  virtual ~Ui() {};
  virtual void draw() =0;
  virtual void update(Scene* scene) =0;
};