#include "SceneDirector.h"
#include <memory>

#include "Scenes/StartScene/StartScene.h"
#include "Scenes/GameScene/GameScene.h"
#include "Scenes/GameOverScene/GameOverScene.h"

SceneDirector::SceneDirector() {
  activeScene = SceneName::START_SCENE;
  scenes.emplace(SceneName::START_SCENE, std::make_unique<StartScene>());
  scenes.emplace(SceneName::GAME_SCENE, std::make_unique<GameScene>());
  scenes.emplace(SceneName::GAME_OVER_SCENE, std::make_unique<GameOverScene>());
  scenes[activeScene]->init();
}

void SceneDirector::changeScene(SceneName sceneName) {
  scenes[activeScene]->uninit();
  activeScene = sceneName;
  scenes[activeScene]->init();
}

void SceneDirector::update() {
  scenes[activeScene]->update(this);
}

void SceneDirector::draw() {
  scenes[activeScene]->draw();
}