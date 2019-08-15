#include "TiledParser.h"
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include "tinyxml2.h"
#include "raylib.h"
#include "helpers.h"

#include <iostream>

TileParser::TileParser() {}

TileParser::TileParser(std::string assetDir, std::string mapName) {
  std::stringstream mapPath;
  mapPath << "../" << assetDir << "/" << mapName;

  tinyxml2::XMLDocument tmxMap;
  tmxMap.LoadFile(mapPath.str().c_str());

  tinyxml2::XMLElement* mapElement = tmxMap.RootElement();
  mapWidth = mapElement->IntAttribute("width");
  mapHeight = mapElement->IntAttribute("height");

  tinyxml2::XMLElement* tilesetElement = mapElement->FirstChildElement("tileset");
  tileWidth = tilesetElement->IntAttribute("tilewidth");
  tileHeight = tilesetElement->IntAttribute("tileheight");
  tileCount = tilesetElement->IntAttribute("tilecount");
  columns = tilesetElement->IntAttribute("columns");

  // TODO: support non embedded tilesets
  std::stringstream tilesetImagePath;
  tilesetImagePath << "../" << assetDir << "/" << tilesetElement->FirstChildElement("image")->Attribute("source");
  tileset = LoadTexture(tilesetImagePath.str().c_str());

  tilemaps = getLayers(mapElement);
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

  // TODO: parse object groups seperately
  // TODO: setup base class for objectgroup items
  // TODO: store in a vector of objects unique_pointer(?)
  // TODO: have a colision check on each object.
  // https://stackoverflow.com/questions/6274136/objects-of-different-classes-in-a-single-vector

  while(layer != NULL && layer->Name() != (std::string)"objectgroup") {
    tilemaps.push_back(parseGidCsv(layer->FirstChildElement("data")->GetText()));
    layer = layer->NextSiblingElement();
  }

  return tilemaps;
}
