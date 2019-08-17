#pragma once

#include "Scene.h"

class GameOverScene: public Scene {
public: 
  void init(); 
  void update(SceneDirector* sceneDirector); 
  void draw(); 
  void uninit();
};