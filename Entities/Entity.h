#pragma once

#include "raylib.h"
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
  Rectangle hitbox{ 0, 0, 16, 16 };
  int scale{3};
public:
  Vector2 position{ 0, 0 };
  Entity();
  Entity(std::string spriteSheetPath, Rectangle hitboxLocation, Vector2 startPosition);

  virtual ~Entity() {
    UnloadTexture(spriteSheet);
   };

  virtual void init(std::string spriteSheetPath, Rectangle hitboxLocation, Vector2 startPosition);
  virtual void draw();
  virtual void update(Actions& actions);
  virtual Vector2 center();
  virtual void uninit();
};