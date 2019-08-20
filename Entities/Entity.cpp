#include "Entity.h"
#include "raylib.h"

#include <string>
#include <iostream>

Entity::Entity() {
};

Entity::Entity(std::string spriteSheetPath, Rectangle hitboxLocation, Vector2 startPosition) {
  spriteSheet = LoadTexture(spriteSheetPath.c_str());
  hitbox = hitboxLocation;
  position = startPosition;
}


void Entity::draw() {
  DrawTexturePro(spriteSheet, {0, 0, 16, 16}, {position.x, position.y, 16.0f * scale, 16.0f * scale}, {0, 0}, 0, WHITE);
}

void Entity::update(Actions& actions) {
  if(actions.moveLeft) {
    position.x -= 3;
  }
  if(actions.moveRight) {
    position.x += 3;
  }
}

void Entity::init(std::string spriteSheetPath, Rectangle hitboxLocation, Vector2 startPosition) {
  spriteSheet = LoadTexture(spriteSheetPath.c_str());
  hitbox = hitboxLocation;
  position = startPosition;
}

void Entity::uninit() {
  UnloadTexture(spriteSheet);
}