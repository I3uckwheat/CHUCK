#pragma once

#include "Scene.h"
#include "Ui.h"
#include "raylib.h"
#include "TiledMap.h"

class GameScene: public Scene {
private:
  TiledMap map;
  Camera2D camera;
  Vector2 player;

public: 
  void init();
  void update(SceneDirector* sceneDirector); 
  void draw(); 
  void uninit();
};