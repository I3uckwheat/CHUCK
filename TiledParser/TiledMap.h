#pragma once

#include "raylib.h"
#include "TiledParser.h"
#include <vector>
#include <string>

class TiledMap {
public:
  TiledMap(std::string assetDir, std::string mapName);
  void draw(const Vector2& offset, const int& screenHeight, const int& screenWidth);
private:
  TileParser mapData;
  void drawLayer(const std::vector<unsigned> tileMap, const Vector2& offset, const int& screenWidth, const int& screenHeight);
  Rectangle getRectAtGid(int gid);
};