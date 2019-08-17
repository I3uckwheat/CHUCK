#pragma once

#include "Scene.h"

class GameOverScene: public Scene {
public: 
  void init() {

  };

  void update(SceneDirector* director) {
    if(IsKeyPressed(KEY_SPACE)) {
      director->changeScene(SceneName::START_SCENE);
    }
  };

  void draw() {
    DrawText("You Died... Press 'SPACE' to restart", 30, 30, 33, BLUE);
  };

  void uninit() {

  };
};