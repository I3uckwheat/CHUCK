#include "TiledMap.h"
#include "TiledParser.h"
#include "helpers.h"
#include "raylib.h"
#include <vector>
#include <string>

static const unsigned FLIPPED_HORIZONTALLY_FLAG = 0x80000000;
static const unsigned FLIPPED_VERTICALLY_FLAG   = 0x40000000;
static const unsigned FLIPPED_DIAGONALLY_FLAG   = 0x20000000;

TiledMap::TiledMap() {}
TiledMap::TiledMap(std::string assetDir, std::string mapName) { mapData = TileParser(assetDir, mapName, 3); }
void TiledMap::load(std::string assetDir, std::string mapName) { mapData = TileParser(assetDir, mapName, 3); }

void TiledMap::unload() {
  UnloadTexture(mapData.tileset);

  // clean up the rest of the data
  mapData.objectGroups.clear();
  mapData.tilemaps.clear();
}

const std::vector<unsigned>& TiledMap::getTilemapLayer(int layer) { return mapData.tilemaps[layer]; };
const std::vector<std::vector<unsigned>>& TiledMap::getTilemapLayers(){ return mapData.tilemaps; };
const MapObjects& TiledMap::getObjectGroup(std::string name){ return mapData.objectGroups[name]; };
const std::unordered_map<std::string, MapObjects>& TiledMap::getObjectGroups() { return mapData.objectGroups; }

void TiledMap::draw(const Vector2& startVector, const int& screenWidth, const int& screenHeight) {
  for(std::vector<unsigned> tilemap : mapData.tilemaps) {
    drawLayer(tilemap, startVector, screenWidth, screenHeight);
  }
}

void TiledMap::drawLayer(const std::vector<unsigned> tileMap, const Vector2& startVector, const int& screenWidth, const int& screenHeight) {
  int scale =  3;

  // Needs to be clamped to prevent drawing tiles from random memory
  int startRow = helpers::clamp(startVector.x / (mapData.tileHeight * scale) - 4, 0.0f, (float)mapData.mapHeight);
  int endRow = helpers::clamp((screenWidth / (mapData.tileWidth * scale)) + startRow + 8, 0, mapData.mapWidth);     // Add an extra tile to prevent visually drawing at edges

  int startCol = helpers::clamp(startVector.y / (mapData.tileWidth * scale) - 4, 0.0f, (float)mapData.mapHeight);
  int endCol = helpers::clamp((screenHeight / (mapData.tileHeight * scale)) + startCol + 8, 0, mapData.mapWidth);

  for(int row = startRow; row < endRow; row++) {
    for(int column = startCol; column < endCol; column++) {
      unsigned maskedGid = tileMap[row + (column * mapData.mapWidth)];

      bool flippedHorizontally = (maskedGid & FLIPPED_HORIZONTALLY_FLAG);
      bool flippedVertically = (maskedGid & FLIPPED_VERTICALLY_FLAG);
      bool flippedDiagonally = (maskedGid & FLIPPED_DIAGONALLY_FLAG);

      int gid = maskedGid & ~(FLIPPED_HORIZONTALLY_FLAG | FLIPPED_VERTICALLY_FLAG | FLIPPED_DIAGONALLY_FLAG);

      Rectangle tileRectangle = getRectAtGid(gid);

      if(flippedDiagonally)   std::swap(tileRectangle.x, tileRectangle.y);
      if(flippedVertically)   tileRectangle.height *= -1;
      if(flippedHorizontally) tileRectangle.width *= -1;

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
