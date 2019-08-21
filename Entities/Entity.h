#pragma once

#include "raylib.h"
#include "TiledMap.h"
#include <string>
#include <iostream>

struct Actions {
  bool moveLeft{false};
  bool moveRight{false};
  bool jump{false};
};

class Entity {
private:
  Texture2D spriteSheet;
  int scale{3};
  Rectangle hitbox{ 0, 0, 16, 16 };
public:
  Vector2 position{ 0, 0 };
  float dx{0};
  float dy{0};
  Entity();
  Entity(std::string spriteSheetPath, Rectangle hitboxLocation, Vector2 startPosition);
  Rectangle getHitBox();

  virtual ~Entity() {
    UnloadTexture(spriteSheet);
   };

  virtual void init(std::string spriteSheetPath, Rectangle hitboxLocation, Vector2 startPosition);
  virtual void draw();
  virtual void update(Actions& actions, TiledMap& map);
  virtual void uninit();
};
