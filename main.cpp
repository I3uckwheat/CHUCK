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

int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    // Importing map1.tmx for csv
    tinyxml2::XMLDocument doc;
    doc.LoadFile("assets/map1.tmx");

    tinyxml2::XMLElement* mapElement = doc.RootElement();
    const int mapWidth = mapElement->IntAttribute("width");   // width in tiles
    const int mapHeight = mapElement->IntAttribute("height"); // Height in tiles

    tinyxml2::XMLElement* tilesetElement = mapElement->FirstChildElement("tileset");
    const int tileWidth = tilesetElement->IntAttribute("tileWidth");
    const int tileHeight = tilesetElement->IntAttribute("tileHeight");
    const int tileCount = tilesetElement->IntAttribute("tilecount");
    const int columns = tilesetElement->IntAttribute("columns");

    tinyxml2::XMLElement* dataElement = mapElement->FirstChildElement("layer")->FirstChildElement("data");
    std::vector<int> gids = parseGidCsv(dataElement->GetText());

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    Texture2D tileset = LoadTexture("assets/ForgottenDungeon.png");

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
            DrawTexturePro(tileset, {0, 0, (float)tileset.width, (float)tileset.height}, {0, 0, screenWidth, screenHeight}, {0, 0}, 0, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

  return 1;
}
