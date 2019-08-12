#include "TileParser.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "tinyxml2.h"
#include "raylib.h"

#include <iostream>

TileParser::TileParser() {
  tinyxml2::XMLDocument tmxMap;
  tmxMap.LoadFile("assets/map1.tmx"); // TODO: make constructor variable

  tinyxml2::XMLElement* mapElement = tmxMap.RootElement();
  mapWidth = mapElement->IntAttribute("width");
  mapHeight = mapElement->IntAttribute("height");

  tinyxml2::XMLElement* tilesetElement = mapElement->FirstChildElement("tileset");
  tileWidth = tilesetElement->IntAttribute("tilewidth");
  tileHeight = tilesetElement->IntAttribute("tileheight");
  tileCount = tilesetElement->IntAttribute("tilecount");
  columns = tilesetElement->IntAttribute("columns");

  std::string tilesetImagePath = "assets/";
  tilesetImagePath += tilesetElement->FirstChildElement("image")->Attribute("source");
  tileset = LoadTexture(tilesetImagePath.c_str());

  tinyxml2::XMLElement* dataElement = mapElement->FirstChildElement("layer")->FirstChildElement("data");
  tilemap = parseGidCsv(dataElement->GetText());
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
  int scale = 3;

  int startRow = -(camera.offset.x) / (tileWidth * scale);
  int startColumn = -(camera.offset.y) / (tileHeight * scale);
  std::cout<<startRow<<" , "<<startColumn<<'\n';

  int maxTilesX = (screenHeight / (tileHeight * scale)) + startColumn - 4;
  int maxTilesY = (screenWidth / (tileWidth * scale)) + startRow - 4;

  for(int row = startRow; row < mapHeight && row < maxTilesY + startRow; row++) {
    for(int column = startColumn; column < mapWidth && column < maxTilesX + startColumn; column++) {
      int tileIndex = row + (column * mapWidth);
      int gid = tilemap[tileIndex];

      Rectangle destRect;
      destRect.x = (row * tileWidth) * scale;
      destRect.y = (column * tileWidth) * scale;
      destRect.width = tileWidth * scale;
      destRect.height = tileHeight * scale;

      DrawTexturePro(tileset, getRectAtGid(gid), destRect, {0, 0}, 0, WHITE);
    }
  }
}

Rectangle TileParser::getRectAtGid(int gid) {
  gid--; // Remove one to get index of 0 instead of id of 1

  Rectangle tile;
  tile.width = tileWidth;
  tile.height = tileHeight;
  tile.x = (gid % columns) * tileWidth; 
  tile.y = (gid / columns) * tileHeight;

  return tile;
}