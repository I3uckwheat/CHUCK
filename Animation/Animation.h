#pragma once

#include <unordered_map>
#include <vector>
#include "raylib.h"

enum class AnimationState {
  IDLE,
  WALK,
  FALL
};

enum class Direction {
  ANY,
  RIGHT,
  LEFT
};

class Animation {
protected:
  bool flipped{ false };
  AnimationState currentAnimation{ AnimationState::IDLE };
  unsigned frame{ 0 };
  unsigned tick{ 0 };

public:
  std::unordered_map<AnimationState, std::vector<Rectangle>> animations;
  Vector2 drawLocation{ 0, 0 };
  virtual ~Animation() {}
  virtual void play(AnimationState Animation, Direction direction){};
  virtual void changeAnimationTo(AnimationState animation){};
};