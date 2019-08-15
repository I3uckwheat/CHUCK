#pragma once

#include "raylib.h"
#include <vector>
#include <string>
#include "tinyxml2.h"

class TileParser {
public:
  int mapWidth{0};
  int mapHeight{0};
  int tileWidth{0};
  int tileHeight{0};
  int tileCount{0};
  int columns{0};

  Texture2D tileset;
  std::vector<std::vector<int>> tilemaps;
  TileParser();
  TileParser(std::string assetDir, std::string mapName);
private:
  std::vector<int> parseGidCsv(const std::string& gidCsv);
  std::vector<std::vector<int>> getLayers(tinyxml2::XMLElement* mapElement);
};
