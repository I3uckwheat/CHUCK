#pragma once

#include "Scene.h"

class StartScene: public Scene {
public: 
  void init() override;
  void update(SceneDirector* sceneDirector) override;
  void draw() override; 
  void uninit() override;
};
