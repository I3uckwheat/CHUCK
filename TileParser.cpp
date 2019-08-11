#include "TileParser.h"
#include <iostream>
#include <vector>
#include <string>
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
  tileWidth = tilesetElement->IntAttribute("tileWidth");
  tileHeight = tilesetElement->IntAttribute("tileHeight");
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

void TileParser::draw() {
  float scale = 0;
  int row = 0;
  int column = 0;
  for(auto i = tilemap.begin(); i != tilemap.end(); ++i) {
    float destX = tileWidth * column;
    float destY = tileHeight * row;

    column++;
    if (column >= mapWidth) {
      row++;
      column = 0;
    }

    DrawTexturePro(tileset, getRectAtGid(*i), {destX * scale, destY * scale, tileHeight * scale, tileWidth * scale}, {0, 0}, 0, WHITE);

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