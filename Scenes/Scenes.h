#pragma once

// #include "SceneDirector.h"
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

class StartScene: public Scene {
public: 
  void init();
  void update();
  void draw();
  void uninit();
};

class GameScene: public Scene {
private:
  TiledMap map;
  Camera2D camera;
  Vector2 player;

public: 
  void init();
  void update(SceneDirector* director);
  void draw();
  void uninit();
};

class GameOverScene: public Scene {
public: 
  void init();
  void update(SceneDirector* director);
  void draw();
  void uninit();
};