#pragma once

#include "raylib.h"
#include <vector>
#include <string>

struct MapData {
  int mapWidth{0};
  int mapHeight{0};
  int tileWidth{0};
  int tileHeight{0};
  int tileCount{0};
  int columns{0};

  Texture2D tileset;
  std::vector<int> tilemap;
};

class TileParser {
public:
  TileParser();
  void draw(Camera2D& camera, int screenHeight, int screenWidth);
private:
  MapData map;
  Rectangle getRectAtGid(int gid);
  std::vector<int> parseGidCsv(std::string gidCsv);
};