#include "Animation.h"
#include "PlayerAnimation.h"

#include <vector>

PlayerAnimation::PlayerAnimation() {
  spriteSheet = LoadTexture("../assets/KNIGHT_WHITE.png");
  animations.insert({AnimationState::IDLE, std::vector<Rectangle>()});
  animations.insert({AnimationState::WALK, std::vector<Rectangle>()});
  // animations.insert({AnimationState::FALL, std::vector<Rectangle>()});

  // Adding idle frames
  for(float i = 0; i < spriteSheet.width; i+=16) {
    animations[AnimationState::IDLE].push_back({i, 0, 16, 16});
  }

  // Adding walking frames
  for(float i = 0; i < spriteSheet.width; i+=16) {
    animations[AnimationState::WALK].push_back({i, 16, 16, 16});
  }

}

void PlayerAnimation::play(AnimationState animation, Direction direction) {
  const float scale = 3;

  if(currentAnimation == AnimationState::IDLE) {
    Rectangle& drawBox = animations[currentAnimation][tick % 4];
    DrawTexturePro(spriteSheet, drawBox, {drawLocation.x, drawLocation.y, 16.0f * scale, 16.0f * scale}, {0, 0}, 0, WHITE);
    currentAnimation = animation;
  }

  if(currentAnimation == AnimationState::WALK) {
    Rectangle& drawBox = animations[currentAnimation][tick % 4];
    DrawTexturePro(spriteSheet, drawBox, {drawLocation.x, drawLocation.y, 16.0f * scale, 16.0f * scale}, {0, 0}, 0, WHITE);
    currentAnimation = animation;
  }

  frame++;
  if (frame % 15 == 0) { // draw next animation frame every 15 frames
    tick++;
  }
}

void PlayerAnimation::changeAnimationTo(AnimationState animation) {
  // TODO make more robust
  // currentAnimation = animation;
}