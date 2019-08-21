#include "Entity.h"
#include "raylib.h"
#include "TiledMap.h"

#include <string>
#include <iostream>

Entity::Entity() {
};

Entity::Entity(std::string spriteSheetPath, Rectangle hitboxLocation, Vector2 startPosition) {
  spriteSheet = LoadTexture(spriteSheetPath.c_str());
  hitbox = hitboxLocation;
  position = startPosition;
  dy = 0;
}


void Entity::draw() {
  DrawTexturePro(spriteSheet, {0, 0, 16, 16}, {position.x, position.y, 16.0f * scale, 16.0f * scale}, {0, 0}, 0, WHITE);
}

void Entity::update(Actions& actions, TiledMap& map) {
  int startx = position.x;

  if(actions.moveLeft) {
    position.x -= 3;
  }
  if(actions.moveRight) {
    position.x += 3;
  }
  if(actions.jump) {
    dy = 3;
  }
  
  // gravity!
  dy += 0.2;
  position.y += dy;

  /* iterate through collision layer */
  bool collision{false};
  Rectangle boxCollision = {};
  for(Rectangle rect : map.getObjectGroup("collisions").rectangle) {
    collision = CheckCollisionRecs(rect, getHitBox()) ;
    if (collision) {
      boxCollision = GetCollisionRec(rect, getHitBox());

      bool bottomCollision = boxCollision.width > boxCollision.height && position.y < boxCollision.y;
      bool topCollision = boxCollision.width > boxCollision.height && position.y == boxCollision.y;
      bool sideCollision = boxCollision.height > boxCollision.width;

      if (bottomCollision) {
        position.y = boxCollision.y - hitbox.height*2;
        dy = 0;
      }

      if (topCollision) {
        position.y = boxCollision.y + boxCollision.height*2 + 1;
        dy = 0;
      }

      if (sideCollision) {
        position.x = startx;
      }
    }
  }
}

Rectangle Entity::getHitBox() {
  Rectangle result;
  result.x = hitbox.x + position.x + hitbox.width;
  result.y = hitbox.y + position.y + hitbox.height;
  result.width = hitbox.width;
  result.height = hitbox.height;
  return result;
}

void Entity::init(std::string spriteSheetPath, Rectangle hitboxLocation, Vector2 startPosition) {
  spriteSheet = LoadTexture(spriteSheetPath.c_str());
  hitbox = hitboxLocation;
  position = startPosition;
}

void Entity::uninit() {
  UnloadTexture(spriteSheet);
}
