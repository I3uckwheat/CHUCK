#include "TiledMap.h"
#include "TiledParser.h"
#include "helpers.h"
#include "raylib.h"
#include <vector>
#include <string>

TiledMap::TiledMap(std::string assetDir, std::string mapName) {
  mapData = TileParser(assetDir, mapName);
}

void TiledMap::draw(const Vector2& offset, const int& screenWidth, const int& screenHeight) {
  for(std::vector<int> tilemap : mapData.tilemaps) {
    drawLayer(tilemap, offset, screenWidth, screenHeight);
  }
}

void TiledMap::drawLayer(const std::vector<int> tileMap, const Vector2& offset, const int& screenWidth, const int& screenHeight) {
  int scale =  2;

  // Needs to be clamped to prevent drawing tiles from random memory
  int startRow = helpers::clamp(-offset.x / (mapData.tileHeight * scale), 0.0f, (float)mapData.mapHeight);
  int startCol = helpers::clamp(-offset.y / (mapData.tileWidth * scale), 0.0f, (float)mapData.mapHeight);

  int endRow = helpers::clamp((screenWidth / (mapData.tileWidth * scale)) + startRow + 2, 0, mapData.mapWidth);     // Add an extra tile to prevent visually drawing at edges
  int endCol = helpers::clamp((screenHeight / (mapData.tileHeight * scale)) + startCol + 2, 0, mapData.mapWidth);

  for(int row = startRow; row < endRow; row++) {
    for(int column = startCol; column < endCol; column++) {
      int tilemapIndex = row + (column * mapData.mapWidth);
      Rectangle tileRectangle = getRectAtGid(tileMap[tilemapIndex]);

      Rectangle destRect;
      destRect.x = (row * mapData.tileWidth) * scale;
      destRect.y = (column * mapData.tileHeight) * scale;
      destRect.width = mapData.tileWidth * scale;
      destRect.height = mapData.tileHeight * scale;

      DrawTexturePro(mapData.tileset, tileRectangle, destRect, {0, 0}, 0, WHITE);
    }
  }
}

Rectangle TiledMap::getRectAtGid(int gid) {
  gid--; // Remove one to get index of 0 instead of id of 1

  Rectangle tile;
  tile.width = mapData.tileWidth;
  tile.height = mapData.tileHeight;
  tile.x = (gid % mapData.columns) * mapData.tileWidth; 
  tile.y = (gid / mapData.columns) * mapData.tileHeight;

  return tile;
}