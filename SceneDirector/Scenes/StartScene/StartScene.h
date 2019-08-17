#pragma once

#include "Scene.h"

class StartScene: public Scene {
public: 
  void init();
  void update(SceneDirector* sceneDirector);
  void draw(); 
  void uninit();
};
