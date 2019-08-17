#include <iostream>
#include <vector>
#include "tinyxml2.h"
#include "raylib.h"
#include "TiledMap.h"
#include "SceneDirector.h"

int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second

    SceneDirector director;
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
      director.update();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            director.draw();

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

  return 1;
}
