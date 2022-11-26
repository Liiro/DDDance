/***
 *
 *   raylib [core] example - Basic window
 *
 *   Welcome to raylib!
 *
 *   To test examples, just press F6 and execute raylib_compile_execute script
 *   Note that compiled executable is placed in the same folder as .c file
 *
 *   You can find all basic examples on C:\raylib\raylib\examples folder or
 *   raylib official webpage: www.raylib.com
 *
 *   Enjoy using raylib. 🙂
 *
 *   Example originally created with raylib 1.0, last time updated with raylib 1.0
 *
 *   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
 *   BSD-like license that allows static linking with closed source software
 *
 *   Copyright (c) 2013-2022 Ramon Santamaria (@raysan5)
 *
 **/

#include "raylib.h"
#include <string>
#include <iostream>
#include <vector>

constexpr float CIRCLE_SPEED_PIXEL = 3.f;
constexpr int CIRCLE_SIZE_PIXELS = 20;

float random_float_01()
{
    return rand() / static_cast<float>(RAND_MAX);
}
struct Position
{
    float x = 0;
    float y = 0;
};
struct arrows
{
    Position position;
};

std::vector<arrows> my_vector; // vector declaration

void update()
{
    arrows arrowsies;

    my_vector.push_back(arrowsies);
}
void render()
{
    BeginDrawing();

    DrawRectangle(50, 700, 700, 100, WHITE);

    DrawRectangle(50, 30, 700, 10, RED);

    DrawCircle(70, 35, 20, WHITE);

    ClearBackground(DARKPURPLE);

    DrawText("Let's Dance!!!", 190, 200, 20, LIGHTGRAY);

    EndDrawing();

    for (int i = 0; i < my_vector.size(); ++i)
    {
        DrawCircle((my_vector[i].position.x),
                   (my_vector[i].position.y), 20, WHITE);
    }
}
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 1400;
    const int screenHeight = 850;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here.
        //----------------------------------------------------------------------------------
        update();
        ClearWindowState(1);

        render();

        // Draw
        //----------------------------------------------------------------------------------
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}