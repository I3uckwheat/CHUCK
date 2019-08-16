#pragma once

#include "raylib.h"
#include <vector>
#include <string>
#include <unordered_map>
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
  std::vector<std::vector<unsigned>> tilemaps;
  std::unordered_map<std::string, std::vector<Rectangle>> objectGroups;
  TileParser();
  TileParser(std::string assetDir, std::string mapName, int scaleAmount);
private:
  int scale{1};
  std::vector<unsigned> parseGidCsv(const std::string& gidCsv);
  std::vector<std::vector<unsigned>> getTileLayers(tinyxml2::XMLElement* mapElement);
  std::unordered_map<std::string, std::vector<Rectangle>> getObjectGroups(tinyxml2::XMLElement* mapElement);
  std::vector<Rectangle> getObjectsFromGroup(tinyxml2::XMLElement* objectgroupElement);
};
