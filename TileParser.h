#pragma once

#include "raylib.h"
#include <vector>
#include <string>
#include <tinyxml2.h>

struct MapData {
  int mapWidth{0};
  int mapHeight{0};
  int tileWidth{0};
  int tileHeight{0};
  int tileCount{0};
  int columns{0};

  Texture2D tileset;
  std::vector<std::vector<int>> tilemaps;
};

class TileParser {
public:
  TileParser(std::string assetDir, std::string mapName);
  void draw(const Vector2& offset, const int& screenHeight, const int& screenWidth);
private:
  MapData map;
  Rectangle getRectAtGid(int gid);
  std::vector<int> parseGidCsv(const std::string& gidCsv);
  void drawLayer(const std::vector<int> tileMap, const Vector2& offset, const int& screenWidth, const int& screenHeight);
  std::vector<std::vector<int>> getLayers(tinyxml2::XMLElement* mapElement);
};