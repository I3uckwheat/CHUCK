#include <iostream>
#include <vector>
#include "tinyxml2.h"
#include "raylib.h"
#include "TiledParser.h"

int main(void) {
  // Initialization
  //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    TileParser map1("assets", "map1.tmx");

    Vector2 player{200, 200};

    Camera2D camera = { 0 };
    camera.target = (Vector2){ player.x + 20, player.y + 20 };
    camera.offset = (Vector2){ 0, 0 };
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;


    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        if(IsKeyDown(KEY_D)) {
          player.x += 3;
          camera.offset.x -= 3;
        }

        if(IsKeyDown(KEY_A)) {
          player.x -= 3;
          camera.offset.x += 3;
        }

        if(IsKeyDown(KEY_S)) {
          player.y += 3;
          camera.offset.y -= 3;
        }

        if(IsKeyDown(KEY_W)) {
          player.y -= 3;
          camera.offset.y += 3;
        }

        camera.target = player;
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);
            BeginMode2D(camera);
              map1.draw({camera.offset.x, camera.offset.y}, screenWidth, screenHeight);
            DrawRectangle(player.x, player.y, 40, 40, RED);
            EndMode2D();


        EndDrawing();
        //----------------------------------------------------------------------------------
    }

  return 1;
}
