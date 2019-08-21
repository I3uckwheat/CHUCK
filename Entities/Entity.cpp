#include "Entity.h"
#include "raylib.h"
#include "Animation.h"

#include <string>
#include <iostream>

Entity::Entity() {
};

Entity::Entity(std::string spriteSheetPath, Rectangle hitboxLocation, Vector2 startPosition) {
  hitbox = hitboxLocation;
  position = startPosition;
}

void Entity::draw() {
  animation.play(AnimationState::WALK, Direction::LEFT);
}

void Entity::update(Actions& actions) {
  animation.drawLocation = position;
  if(actions.moveLeft) {
    position.x -= 3;
    // animation.play(AnimationState::WALK, Direction::LEFT);
  } else if(actions.moveRight) {
    position.x += 3;
    // animation.play(AnimationState::WALK, Direction::RIGHT);
  } else {
    animation.play(AnimationState::IDLE, Direction::ANY);
  }
}

void Entity::init(std::string spriteSheetPath, Rectangle hitboxLocation, Vector2 startPosition) {
  spriteSheet = LoadTexture(spriteSheetPath.c_str());
  hitbox = hitboxLocation;
  position = startPosition;
}

void Entity::uninit() {
}