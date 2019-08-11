#include <iostream>
#include "stdio.h"
#include "tinyxml2.h"
#include "raylib.h"

int main(void) {
  tinyxml2::XMLDocument doc;
  doc.LoadFile("assets/test.tsx");

  const char* value = doc.FirstChildElement()->FirstChildElement()->Attribute("width");
  std::cout << value << '\n';

// Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    // Texture2D tileset = LoadTexture("assets/TileSet.png");

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
            // DrawTexturePro(tileset, {841, , 25, 25}, {0, 0, screenWidth, screenHeight}, {0, 0}, 0, WHITE);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

  return 1;
}
