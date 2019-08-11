#pragma once

#include "raylib.h"
#include <vector>
#include <string>

class TileParser {
public:
  TileParser();
  void draw();
private:
  int mapWidth;
  int mapHeight;
  int tileWidth;
  int tileHeight;
  int tileCount;
  int columns;
  Texture2D tileset;
  std::vector<int> tilemap;

  std::vector<int> parseGidCsv(std::string gidCsv);
  Rectangle getRectAtGid(int gid);
};