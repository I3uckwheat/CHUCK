#pragma once

#include "raylib.h"
#include "TiledParser.h"
#include <vector>
#include <string>

class TiledMap {
public:
  TiledMap();
  TiledMap(std::string assetDir, std::string mapName);
  void load(std::string assetDir, std::string mapName);
  void draw(const Vector2& offset, const int& screenHeight, const int& screenWidth);

  void unload();

  // Getters
  const std::vector<unsigned>& getTilemapLayer(int layer);
  const std::vector<std::vector<unsigned>>& getTilemapLayers();
  const MapObjects& getObjectGroup(std::string name);
  const std::unordered_map<std::string, MapObjects>& getObjectGroups();
private:
  TileParser mapData;
  void drawLayer(const std::vector<unsigned> tileMap, const Vector2& offset, const int& screenWidth, const int& screenHeight);
  Rectangle getRectAtGid(int gid);
};