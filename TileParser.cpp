#include "TileParser.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "tinyxml2.h"
#include "raylib.h"
#include "helpers.h"

#include <iostream>

TileParser::TileParser(std::string assetDir, std::string mapName) {
  std::stringstream mapPath;
  mapPath << assetDir << "/" << mapName;

  tinyxml2::XMLDocument tmxMap;
  tmxMap.LoadFile(mapPath.str().c_str());

  tinyxml2::XMLElement* mapElement = tmxMap.RootElement();
  map.mapWidth = mapElement->IntAttribute("width");
  map.mapHeight = mapElement->IntAttribute("height");

  tinyxml2::XMLElement* tilesetElement = mapElement->FirstChildElement("tileset");
  map.tileWidth = tilesetElement->IntAttribute("tilewidth");
  map.tileHeight = tilesetElement->IntAttribute("tileheight");
  map.tileCount = tilesetElement->IntAttribute("tilecount");
  map.columns = tilesetElement->IntAttribute("columns");

  // TODO: support non embedded tilesets
  std::stringstream tilesetImagePath;
  tilesetImagePath << assetDir << "/" << tilesetElement->FirstChildElement("image")->Attribute("source");
  map.tileset = LoadTexture(tilesetImagePath.str().c_str());

  // TODO: convert to vector with all maps
  // tinyxml2::XMLElement* dataElement = mapElement->FirstChildElement("layer")->FirstChildElement("data");
  // map.tilemaps.push_back(parseGidCsv(dataElement->GetText()));

  map.tilemaps = getLayers(mapElement);
}

std::vector<int> TileParser::parseGidCsv(const std::string& gidCsv) {
  std::vector<int> numVector;

  // str.find works with positions, not indexes
  std::size_t currentStringPos = 1;

  while(currentStringPos != 0) {
    std::size_t delimiterPos = gidCsv.find(',', currentStringPos);
    numVector.push_back(std::stoi(gidCsv.substr(currentStringPos, delimiterPos)));
    currentStringPos = delimiterPos + 1;
  }

  return numVector;
}

std::vector<std::vector<int>> TileParser::getLayers(tinyxml2::XMLElement* mapElement) {
  std::vector<std::vector<int>> tilemaps;
  tinyxml2::XMLElement* layer = mapElement->FirstChildElement("layer");
  while(layer != NULL) {
    tilemaps.push_back(parseGidCsv(layer->FirstChildElement("data")->GetText()));
    layer = layer->NextSiblingElement();
  }

  return tilemaps;
}

void TileParser::draw(const Vector2& offset, const int& screenWidth, const int& screenHeight) {
  for(std::vector<int> tilemap : map.tilemaps) {
    drawLayer(tilemap, offset, screenWidth, screenHeight);
  }
}

void TileParser::drawLayer(const std::vector<int> tileMap, const Vector2& offset, const int& screenWidth, const int& screenHeight) {
  int scale =  2;

  // Needs to be clamped to prevent drawing tiles from random memory
  int startRow = helpers::clamp(-offset.x / (map.tileHeight * scale), 0.0f, (float)map.mapHeight);
  int startCol = helpers::clamp(-offset.y / (map.tileWidth * scale), 0.0f, (float)map.mapHeight);

  // Needs to be clamped to prevent drawing tiles from random memory
  int endRow = helpers::clamp((screenWidth / (map.tileWidth * scale)) + startRow + 2, 0, map.mapWidth);     // Add an extra tile to prevent visually drawing at edges
  int endCol = helpers::clamp((screenHeight / (map.tileHeight * scale)) + startCol + 2, 0, map.mapHeight);

  for(int row = startRow; row < endRow; row++) {
    for(int column = startCol; column < endCol; column++) {
      int tilemapIndex = row + (column * map.mapWidth);
      Rectangle tileRectangle = getRectAtGid(tileMap[tilemapIndex]);

      Rectangle destRect;
      destRect.x = (row * map.tileWidth) * scale;
      destRect.y = (column * map.tileWidth) * scale;
      destRect.width = map.tileWidth * scale;
      destRect.height = map.tileHeight * scale;

      DrawTexturePro(map.tileset, tileRectangle, destRect, {0, 0}, 0, WHITE);
    }
  }
}

Rectangle TileParser::getRectAtGid(int gid) {
  gid--; // Remove one to get index of 0 instead of id of 1

  Rectangle tile;
  tile.width = map.tileWidth;
  tile.height = map.tileHeight;
  tile.x = (gid % map.columns) * map.tileWidth; 
  tile.y = (gid / map.columns) * map.tileHeight;

  return tile;
}