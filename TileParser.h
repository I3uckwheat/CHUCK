#pragma once

#include "raylib.h"
#include <vector>
#include <string>

class TileParser {
public:
  TileParser();
  void draw();
private:
  int mapWidth{0};
  int mapHeight{0};
  int tileWidth{0};
  int tileHeight{0};
  int tileCount{0};
  int columns{0};

  Texture2D tileset;
  std::vector<int> tilemap;

  std::vector<int> parseGidCsv(std::string gidCsv);
  Rectangle getRectAtGid(int gid);
};