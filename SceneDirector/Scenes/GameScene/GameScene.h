#pragma once

#include "Scene.h"
#include "Ui.h"
#include "raylib.h"
#include "TiledMap.h"
#include "Entity.h"
#include <vector>
#include <memory>

class GameScene: public Scene {
private:
  Entity player;
  TiledMap map;
  Camera2D camera;
  std::vector<std::unique_ptr<Entity>> entities;
  std::vector<std::unique_ptr<Ui>> uiLayers;

public: 
  void init() override;
  void update(SceneDirector* sceneDirector) override; 
  void draw() override; 
  void uninit() override;
};