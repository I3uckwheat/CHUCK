#include "TileParser.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "tinyxml2.h"
#include "raylib.h"
#include "helpers.h"

#include <iostream>

TileParser::TileParser() {
  tinyxml2::XMLDocument tmxMap;
  tmxMap.LoadFile("assets/map1.tmx"); // TODO: make constructor variable

  tinyxml2::XMLElement* mapElement = tmxMap.RootElement();
  map.mapWidth = mapElement->IntAttribute("width");
  map.mapHeight = mapElement->IntAttribute("height");

  tinyxml2::XMLElement* tilesetElement = mapElement->FirstChildElement("tileset");
  map.tileWidth = tilesetElement->IntAttribute("tilewidth");
  map.tileHeight = tilesetElement->IntAttribute("tileheight");
  map.tileCount = tilesetElement->IntAttribute("tilecount");
  map.columns = tilesetElement->IntAttribute("columns");

  std::string tilesetImagePath = "assets/";
  tilesetImagePath += tilesetElement->FirstChildElement("image")->Attribute("source");
  map.tileset = LoadTexture(tilesetImagePath.c_str());

  tinyxml2::XMLElement* dataElement = mapElement->FirstChildElement("layer")->FirstChildElement("data");
  map.tilemap = parseGidCsv(dataElement->GetText());
}

std::vector<int> TileParser::parseGidCsv(std::string gidCsv) {
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


void TileParser::draw(Camera2D& camera, int screenWidth, int screenHeight) {
  // TODO: bounds checking (no negatives, or drawing outside of map)
  int scale =  2;

  // Needs to be clamped to prevent drawing tiles from random memory
  int startRow = helpers::clamp(-camera.offset.x / (map.tileHeight * scale), 0.0f, (float)map.mapHeight);
  int startCol = helpers::clamp(-camera.offset.y / (map.tileWidth * scale), 0.0f, (float)map.mapHeight);

  // Needs to be clamped to prevent drawing tiles from random memory
  int endRow = helpers::clamp((screenWidth / (map.tileWidth * scale)) + startRow + 2, 0, map.mapWidth);     // Add an extra tile to prevent visually drawing at edges
  int endCol = helpers::clamp((screenHeight / (map.tileHeight * scale)) + startCol + 2, 0, map.mapHeight);

  for(int row = startRow; row < endRow; row++) {
    for(int column = startCol; column < endCol; column++) {
      int tilemapIndex = row + (column * map.mapWidth);
      Rectangle tileRectangle = getRectAtGid(map.tilemap[tilemapIndex]);

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