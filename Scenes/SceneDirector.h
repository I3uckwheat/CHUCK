#pragma once

#include "Scenes.h"
#include <unordered_map>
#include <memory>

enum class SceneName {
  START_SCENE,
  GAME_SCENE,
  GAME_OVER_SCENE
};

class SceneDirector {
private:
  SceneName activeScene{SceneName::GAME_SCENE};
  std::unordered_map<SceneName, std::unique_ptr<Scene>> scenes;
public:
  SceneDirector();
  void changeScene(SceneName sceneName);
  void draw();
  void update();
};