#pragma once

#include "Scene.h"
#include "Ui.h"
#include "raylib.h"
#include "TiledMap.h"
#include "stack"
#include <memory>

class GameScene: public Scene {
private:
  TiledMap map;
  Camera2D camera;
  Vector2 player;

public: 
  std::stack<std::unique_ptr<Ui>> uiStack;
  void init() override;
  void update(SceneDirector* sceneDirector) override; 
  void draw() override; 
  void uninit() override;
};