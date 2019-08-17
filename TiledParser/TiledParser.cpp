#include "TiledParser.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
#include <sstream>
#include <algorithm>
#include "tinyxml2.h"
#include "raylib.h"
#include "helpers.h"

#include <iostream>

TileParser::TileParser() {}

TileParser::TileParser(std::string assetDir, std::string mapName, int scaleAmount) {
  scale = scaleAmount;

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

  tilemaps = getTileLayers(mapElement);
  objectGroups = getObjectGroups(mapElement);
}

std::vector<unsigned> TileParser::parseGidCsv(const std::string& gidCsv) {
  std::vector<unsigned> numVector;

  // str.find works with positions, not indexes
  std::size_t currentStringPos = 1;

  while(currentStringPos != 0) {
    std::size_t delimiterPos = gidCsv.find(',', currentStringPos);
    numVector.push_back(std::stoul(gidCsv.substr(currentStringPos, delimiterPos)));
    currentStringPos = delimiterPos + 1;
  }

  return numVector;
}

std::vector<std::vector<unsigned>> TileParser::getTileLayers(tinyxml2::XMLElement* mapElement) {
  std::vector<std::vector<unsigned>> tilemaps;
  tinyxml2::XMLElement* layer = mapElement->FirstChildElement("layer");

  while(layer != NULL) {
    tilemaps.push_back(parseGidCsv(layer->FirstChildElement("data")->GetText()));
    layer = layer->NextSiblingElement("layer");
  }

  return tilemaps;
}

std::unordered_map<std::string, std::vector<Rectangle>> TileParser::getObjectGroups(tinyxml2::XMLElement* mapElement) {
  std::unordered_map<std::string, std::vector<Rectangle>> objectGroups;
  tinyxml2::XMLElement* layer = mapElement->FirstChildElement("objectgroup");

  while(layer != NULL) {
    objectGroups.emplace(layer->Attribute("name"), getObjectsFromGroup(layer));
    layer = layer->NextSiblingElement("objectgroup");
  }

  return objectGroups;
}

std::vector<Rectangle> TileParser::getObjectsFromGroup(tinyxml2::XMLElement* objectgroupElement) {
  std::vector<Rectangle> objects;
  tinyxml2::XMLElement* object = objectgroupElement->FirstChildElement("object");
  while(object != NULL) {
    if (object->NoChildren()) { // If a rectangle, rectangle nodes have no children
      float objX = object->FloatAttribute("x") * scale;
      float objY = object->FloatAttribute("y") * scale;
      float objWidth = object->FloatAttribute("width", 0.0f) * scale;
      float objHeight = object->FloatAttribute("height", 0.0f) * scale;

      objects.push_back({objX, objY, objWidth, objHeight});
    } else {
      std::cerr<<"\033[1;31mTiledParser: All objects must be rectangles in object layers\033[0m\n";
      exit(1);
    }
    object = object->NextSiblingElement("object");
  }

  return objects;
}