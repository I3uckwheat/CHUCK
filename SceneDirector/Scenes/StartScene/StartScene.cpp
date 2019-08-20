#include "StartScene.h"

#include "raylib.h"

void StartScene::init() {}
void StartScene::update(SceneDirector* sceneDirector) {
  if(IsKeyPressed(KEY_SPACE)) {
    sceneDirector->changeScene(SceneName::GAME_SCENE);
  }
}

void StartScene::draw() {
  DrawText("PRESS SPACE TO START AND 'P' TO DIE", 30, 30, 33, BLUE);
}

void StartScene::uninit() {}