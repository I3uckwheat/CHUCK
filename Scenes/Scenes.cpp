#include "Scenes.h"
#include "SceneDirector.h"

// Start
void StartScene::init() {};
void StartScene::update() {};
void StartScene::draw() {};
void StartScene::uninit() {};

// Game
void GameScene::init() {
  map.load("./assets", "map2.tmx");

  player = {200, 200};

  camera = { 0 };
  camera.target = (Vector2){ player.x + 20, player.y + 20 };
  camera.offset = (Vector2){ 0, 0 };
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;
}

void GameScene::update(SceneDirector* director) {
  if(IsKeyDown(KEY_P)) {
    director->changeScene(SceneName::GAME_OVER_SCENE);
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

void GameScene::uninit() { map.unload(); }

// Game over
void GameOverScene::init() {}
void GameOverScene::update(SceneDirector* director) {}
void GameOverScene::draw() {
  DrawText("You Failed", 20, 20, 12, RED);
}
void GameOverScene::uninit() {}