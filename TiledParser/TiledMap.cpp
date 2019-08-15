#include "TiledMap.h"
#include "TiledParser.h"
#include "helpers.h"
#include "raylib.h"
#include <vector>
#include <string>

TiledMap::TiledMap(std::string assetDir, std::string mapName) {
  TileParser tileParser(assetDir, mapName);
  mapData.width = tileParser.map.mapWidth;
  mapData.height = tileParser.map.mapHeight;

  spriteSheet.columns = tileParser.map.columns;
  spriteSheet.count = tileParser.map.tileCount;
  spriteSheet.tileWidth = tileParser.map.tileWidth;
  spriteSheet.tileHeight = tileParser.map.tileHeight;
  spriteSheet.texture = tileParser.map.tileset;

  tilemaps = tileParser.getTilemaps();
}

void TiledMap::draw(const Vector2& offset, const int& screenWidth, const int& screenHeight) {
  for(std::vector<int> tilemap : tilemaps) {
    drawLayer(tilemap, offset, screenWidth, screenHeight);
  }
}

void TiledMap::drawLayer(const std::vector<int> tileMap, const Vector2& offset, const int& screenWidth, const int& screenHeight) {
  int scale =  2;

  // Needs to be clamped to prevent drawing tiles from random memory
  int startRow = helpers::clamp(-offset.x / (spriteSheet.tileHeight * scale), 0.0f, (float)mapData.height);
  int endRow = helpers::clamp((screenWidth / (spriteSheet.tileHeight * scale)) + startRow + 2, 0, mapData.height);     // Add an extra tile to prevent visually drawing at edges

  int startCol = helpers::clamp(-offset.y / (spriteSheet.tileWidth * scale), 0.0f, (float)mapData.width);
  int endCol = helpers::clamp((screenHeight / (spriteSheet.tileWidth * scale)) + startCol + 2, 0, mapData.width);

  for(int row = startRow; row < endRow; row++) {
    for(int column = startCol; column < endCol; column++) {
      int tilemapIndex = row + (column * mapData.width);
      Rectangle tileRectangle = getRectAtGid(tileMap[tilemapIndex]);

      Rectangle destRect;
      destRect.x = (row * spriteSheet.tileWidth) * scale;
      destRect.y = (column * spriteSheet.tileWidth) * scale;
      destRect.width = spriteSheet.tileWidth * scale;
      destRect.height = spriteSheet.tileHeight * scale;

      DrawTexturePro(spriteSheet.texture, tileRectangle, destRect, {0, 0}, 0, WHITE);
    }
  }
}

Rectangle TiledMap::getRectAtGid(int gid) {
  gid--; // Remove one to get index of 0 instead of id of 1

  Rectangle tile;
  tile.width = mapData.width;
  tile.height = mapData.height;
  tile.x = (gid % spriteSheet.columns) * spriteSheet.tileWidth; 
  tile.y = (gid / spriteSheet.columns) * spriteSheet.tileHeight;

  return tile;
}