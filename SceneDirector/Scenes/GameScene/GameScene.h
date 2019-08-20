#pragma once

#include "Scene.h"
#include "Ui.h"
#include "raylib.h"
#include "TiledMap.h"
#include <vector>
#include <memory>

class GameScene: public Scene {
private:
  TiledMap map;
  Camera2D camera;
  Vector2 player;
  std::vector<std::unique_ptr<Ui>> uiLayers;

public: 
  void init() override;
  void update(SceneDirector* sceneDirector) override; 
  void draw() override; 
  void uninit() override;
};