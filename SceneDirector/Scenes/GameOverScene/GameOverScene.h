#pragma once

#include "Scene.h"

class GameOverScene: public Scene {
public: 
  void init() override; 
  void update(SceneDirector* sceneDirector) override; 
  void draw() override; 
  void uninit() override;
};