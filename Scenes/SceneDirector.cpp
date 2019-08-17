#include "SceneDirector.h"
#include <memory>

#include "Scenes.h"

SceneDirector::SceneDirector() {
  activeScene = SceneName::GAME_SCENE;
  scenes.emplace(SceneName::GAME_SCENE, std::make_unique<GameScene>());
  scenes.emplace(SceneName::GAME_OVER_SCENE, std::make_unique<GameOverScene>());
  scenes[activeScene]->init();
}

void SceneDirector::changeScene(SceneName sceneName) {
  activeScene = sceneName;
  scenes[activeScene]->init();
}

void SceneDirector::update() {
  scenes[activeScene]->update(this);
}

void SceneDirector::draw() {
  scenes[activeScene]->draw();
}