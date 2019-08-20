#include "GameScene.h"
#include "SceneDirector.h"
#include "./GameSceneUi.h"

#include <memory>

#include "raylib.h"
#include "Entity.h"

void GameScene::init() {
  map.load("./assets", "map2.tmx");

  uiLayers.emplace_back(std::make_unique<GameSceneUi>());
  player.init("../assets/KNIGHT_WHITE.png", Rectangle{0, 0, 16, 16}, Vector2{60, 120});

  camera = { 0 };
  camera.target = (Vector2){ 0, 0 };
  camera.offset = (Vector2){ 0, 0 };
  camera.rotation = 0.0f;
  camera.zoom = 1.0f;
}

void GameScene::update(SceneDirector* sceneDirector) {
  if(!uiLayers.back()->hasKeyboardControl()) {
    if(IsKeyDown(KEY_P)) {
      sceneDirector->changeScene(SceneName::GAME_OVER_SCENE);
    }

    Actions playerAction;

    if(IsKeyDown(KEY_D)) {
      playerAction.moveRight = true;
      camera.offset.x -= 3;
    }

    if(IsKeyDown(KEY_A)) {
      playerAction.moveLeft = true;
      camera.offset.x += 3;
    }

    camera.target = player.center();

    player.update(playerAction);
  }

  uiLayers.back()->update(uiLayers);
}

void GameScene::draw() {
  BeginMode2D(camera);
  map.draw({camera.offset.x, camera.offset.y}, GetScreenWidth(), GetScreenHeight());
  player.draw();
  EndMode2D();

  for(auto&& layerPtr: uiLayers) {
    layerPtr->draw();
  }
}

void GameScene::uninit() { 
  player.uninit();
  map.unload(); 
}