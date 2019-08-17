#include "GameScene.h"
#include "SceneDirector.h"

void GameScene::init() {
  map.load("./assets", "map2.tmx");

  player = {200, 200};

  camera = { 0 };
  camera.target = (Vector2){ player.x + 20, player.y + 20 };
  camera.offset = (Vector2){ 0, 0 };
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;
}

void GameScene::update(SceneDirector* sceneDirector) {
  if(IsKeyDown(KEY_P)) {
    sceneDirector->changeScene(SceneName::GAME_OVER_SCENE);
  }

  if(IsKeyDown(KEY_D)) {
    player.x += 3;
    camera.offset.x -= 3;
  }

  if(IsKeyDown(KEY_A)) {
    player.x -= 3;
    camera.offset.x += 3;
  }

  if(IsKeyDown(KEY_S)) {
    player.y += 3;
    camera.offset.y -= 3;
  }

  if(IsKeyDown(KEY_W)) {
    player.y -= 3;
    camera.offset.y += 3;
  }

  camera.target = player;
}

void GameScene::draw() {
  BeginMode2D(camera);
  map.draw({camera.offset.x, camera.offset.y}, GetScreenWidth(), GetScreenHeight());
  DrawRectangle(player.x, player.y, 40, 40, RED);
  EndMode2D();
}

void GameScene::uninit() { 
  map.unload(); 
}