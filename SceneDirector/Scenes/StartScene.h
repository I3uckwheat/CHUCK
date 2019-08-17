#pragma once

#include "Scene.h"

class StartScene: public Scene {
public: 
  void init() {

  };

  void update(SceneDirector* director) {
    if(IsKeyPressed(KEY_SPACE)) {
      director->changeScene(SceneName::GAME_SCENE);
    }
  };

  void draw() {
    DrawText("PRESS SPACE TO START AND 'P' TO DIE", 30, 30, 33, BLUE);
  };

  void uninit() {

  };
};
