#pragma once

#include "raylib.h"
#include "TiledParser.h"
#include <vector>
#include <string>

struct MapData {
  int width;
  int height;
};

struct SpriteSheet {
  int count{0};
  int columns{0};
  int tileWidth{0};
  int tileHeight{0};

  Texture2D texture;
};

class TiledMap {
public:
  TiledMap(std::string assetDir, std::string mapName);
  void draw(const Vector2& offset, const int& screenHeight, const int& screenWidth);
private:
  MapData mapData;
  SpriteSheet spriteSheet;
  std::vector<std::vector<int>> tilemaps;

  void drawLayer(const std::vector<int> tileMap, const Vector2& offset, const int& screenWidth, const int& screenHeight);
  Rectangle getRectAtGid(int gid);
};