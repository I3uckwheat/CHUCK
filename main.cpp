#include <iostream>
#include <vector>
#include "tinyxml2.h"
#include "raylib.h"

std::vector<int> parseGidCsv(std::string csv) {
  std::vector<int> numVector;

  // str.find works with positions, not indexes
  std::size_t currentStringPos = 1;

  while(currentStringPos != 0) {
    std::size_t delimiterPos = csv.find(',', currentStringPos);
    numVector.push_back(std::stoi(csv.substr(currentStringPos, delimiterPos)));
    currentStringPos = delimiterPos + 1;
  }

  return numVector;
}

struct MapData {
  int mapWidth;
  int mapHeight;
  int tileWidth;
  int tileHeight;
  int tileCount;
  int columns;
  std::vector<int> gids; // Maybe store rectangles
  Texture2D tileset;

  Rectangle getRectAtGid(int gid) {
    gid--; // Remove one to get index of 0 instead of id of 1

    Rectangle tile;
    tile.width = tileWidth;
    tile.height = tileHeight;
    tile.x = (gid % columns) * tileWidth; 
    tile.y = (gid / columns) * tileHeight;

    return tile;
  }
};

int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    // Importing map1.tmx for csv
    tinyxml2::XMLDocument doc;
    doc.LoadFile("assets/map1.tmx");

    MapData map1;

    tinyxml2::XMLElement* mapElement = doc.RootElement();
    map1.mapWidth = mapElement->IntAttribute("width");   // width in tiles
    map1.mapHeight = mapElement->IntAttribute("height"); // Height in tiles

    tinyxml2::XMLElement* tilesetElement = mapElement->FirstChildElement("tileset");
    map1.tileWidth = tilesetElement->IntAttribute("tilewidth");
    map1.tileHeight = tilesetElement->IntAttribute("tileheight");
    map1.tileCount = tilesetElement->IntAttribute("tilecount");
    map1.columns = tilesetElement->IntAttribute("columns");

    std::string tilesetPath = "assets/";
    tilesetPath += tilesetElement->FirstChildElement("image")->Attribute("source");
    map1.tileset = LoadTexture(tilesetPath.c_str());

    tinyxml2::XMLElement* dataElement = mapElement->FirstChildElement("layer")->FirstChildElement("data");
    map1.gids = parseGidCsv(dataElement->GetText());

    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            float scale = 3;
            int row = 0;
            int column = 0;
            for(auto i = map1.gids.begin(); i != map1.gids.end(); ++i) {
              float destX = map1.tileWidth * column;
              float destY = map1.tileHeight * row;

              column++;
              if (column >= map1.mapWidth) {
                row++;
                column = 0;
              }

              DrawTexturePro(map1.tileset, map1.getRectAtGid(*i), {destX * scale, destY * scale, map1.tileHeight * scale, map1.tileWidth * scale}, {0, 0}, 0, WHITE);

            }

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

  return 1;
}
