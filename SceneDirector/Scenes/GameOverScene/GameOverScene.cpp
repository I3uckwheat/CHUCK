#include "GameOverScene.h"

void GameOverScene::init() {}

void GameOverScene::update(SceneDirector* sceneDirector) {
  if(IsKeyPressed(KEY_SPACE)) {
    sceneDirector->changeScene(SceneName::START_SCENE);
  }
}

void GameOverScene::draw() {
  DrawText("You Died... Press 'SPACE' to restart", 30, 30, 33, BLUE);
}

void GameOverScene::uninit() {}