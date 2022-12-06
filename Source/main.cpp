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

#define MAX_FRAME_DELAY 20
#define MIN_FRAME_DELAY 1

constexpr float CIRCLE_SPEED_PIXEL = 3.f;
constexpr int CIRCLE_SIZE_PIXELS = 20;

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //-------------------------------------------------------------------------------------------------------

    int random_float = 0.1f;

    InitAudioDevice();
    constexpr int screenWidth = 1400;
    constexpr int screenHeight = 850;
    InitWindow(screenWidth, screenHeight, "DDDance!!!");

    int animFrames = 0;
    unsigned int nextFrameDataOffset = 0;

    int currentAnimFrame = 0; // Current animation frame to load and draw
    int frameDelay = 8;       // Frame delay to switch between animation frames
    int frameCounter = 0;     // General frames counter

    Sound mosik = LoadSound("C:\\Users\\Liash\\Desktop\\DDDance\\Source\\resources\\awo.wav");
    Sound kuso = LoadSound("C:\\Users\\Liash\\Desktop\\DDDance\\Source\\resources\\kuso.wav");
    Sound hitsound = LoadSound("C:\\Users\\Liash\\Desktop\\DDDance\\Source\\resources\\hitSound.wav");

    Image pepemosik = LoadImageAnim("C:\\Users\\Liash\\Desktop\\DDDance\\Source\\resources\\mosik.gif", &animFrames);
    Image pepemosikdos = LoadImageAnim("C:\\Users\\Liash\\Desktop\\DDDance\\Source\\resources\\mosikDos.gif", &animFrames);

    Texture2D pepeTexture = LoadTextureFromImage(pepemosik);
    Texture2D pepeTexturedos = LoadTextureFromImage(pepemosikdos);

    Texture2D texture = LoadTexture("C:\\Users\\Liash\\Desktop\\DDDance\\Source\\resources\\audacity.png");

    Texture2D arrowDown = LoadTexture("C:\\Users\\Liash\\Desktop\\DDDance\\Source\\resources\\arrowDown.png");
    Image arrowDownImg = LoadImage("C:\\Users\\Liash\\Desktop\\DDDance\\Source\\resources\\arrowDown.png"); // NOT WORKING
    Texture2D arrowUp = LoadTexture("C:\\Users\\Liash\\Desktop\\DDDance\\Source\\resources\\arrowUp.png");
    Texture2D arrowLeft = LoadTexture("C:\\Users\\Liash\\Desktop\\DDDance\\Source\\resources\\arrowLeft.png");
    Texture2D arrowRight = LoadTexture("C:\\Users\\Liash\\Desktop\\DDDance\\Source\\resources\\arrowRight.png");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {

        // Update
        //-------------------------------------------------------------------------------------------------------

        frameCounter++;
        if (frameCounter >= frameDelay)
        {
            currentAnimFrame++;
            if (currentAnimFrame >= animFrames)
                currentAnimFrame = 0;

            nextFrameDataOffset = pepemosik.width * pepemosik.height * 4 * currentAnimFrame;
            UpdateTexture(pepeTexture, ((unsigned char *)pepemosik.data) + nextFrameDataOffset);
            nextFrameDataOffset = pepemosikdos.width * pepemosikdos.height * 4 * currentAnimFrame;
            UpdateTexture(pepeTexturedos, ((unsigned char *)pepemosikdos.data) + nextFrameDataOffset);

            frameCounter = 0;
        }

        // control pepe speed
        if (IsKeyPressed(KEY_RIGHT))
            frameDelay++;
        else if (IsKeyPressed(KEY_LEFT))
            frameDelay--;
        if (frameDelay > MAX_FRAME_DELAY)
            frameDelay = MAX_FRAME_DELAY;
        else if (frameDelay < MIN_FRAME_DELAY)
            frameDelay = MIN_FRAME_DELAY;

        // control mosik playing status ON OFF
        if (IsKeyPressed(KEY_SPACE))
        {
            IsSoundPlaying(mosik) ? PauseSound(mosik) : PlaySound(mosik);
        };

        // do something when we press W S A D keys
        if (IsKeyPressed(KEY_W))
        {
            PlaySound(hitsound);
        }
        if (IsKeyPressed(KEY_S))
        {
            PlaySound(hitsound);
        }
        if (IsKeyPressed(KEY_A))
        {
            PlaySound(hitsound);
        }
        if (IsKeyPressed(KEY_D))
        {
            PlaySound(hitsound);
        }
        if (IsKeyPressed(KEY_K))
        {
            PlaySound(kuso);
        }

        //----------------------------------------------------------------------------------
        // TODO: Update your variables here.
        //----------------------------------------------------------------------------------

        // Draw
        //-----------------------------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(WHITE);

        IsSoundPlaying(mosik) ? DrawText("Press SPACE to PAUSE MOSIK!", 400, 180, 30, LIGHTGRAY) : DrawText("Press SPACE to PLAY MOSIK!", 400, 180, 30, LIGHTGRAY);
        DrawText("Press K to PLAY KUSO!", 400, 120, 30, LIGHTGRAY);

        DrawTexture(texture, -300, 0, WHITE); // does show up issue was the image path

        DrawText("Press LEFT to make PEPE DANCE FASTER!", 700, 700, 30, LIGHTGRAY);

        DrawText("Press RIGHT to make PEPE DANCE SLOWER!", 700, 800, 30, LIGHTGRAY);

        DrawTexture(pepeTexture, 700, 400, WHITE);
        DrawTexture(pepeTexturedos, 1000, 200, WHITE);

        DrawTexture(arrowDown, 500, 450, BLACK);
        ImageDrawPixel(&arrowDownImg, 560, 600, RED); // NOT WORKING
        DrawTexture(arrowUp, 500, 350, BLACK);
        DrawTexture(arrowLeft, 400, 400, BLACK);
        DrawTexture(arrowRight, 600, 400, BLACK);

        DrawCircle(20, 40, 16, RED);

        EndDrawing();
        //-----------------------------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadSound(mosik);            // Unload sound data
    CloseAudioDevice();            // Close audio device
    UnloadTexture(pepeTexture);    // Unload texture
    UnloadImage(pepemosik);        // Unload image (contains all frames)
    UnloadTexture(pepeTexturedos); // Unload texture
    UnloadImage(pepemosikdos);     // Unload image (contains all frames)
    CloseWindow();                 // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}