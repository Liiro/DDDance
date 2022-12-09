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
#include <filesystem>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------
#define MAX_FRAME_DELAY 20
#define MIN_FRAME_DELAY 1

//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------
constexpr float CIRCLE_SPEED_PIXEL = 3.f;
constexpr int CIRCLE_SIZE_PIXELS = 20;
constexpr int screenWidth = 1400;
constexpr int screenHeight = 850;
int animFrames = 0;
unsigned int nextFrameDataOffset = 0;
int currentAnimFrame = 0; // Current animation frame to load and draw
int frameDelay = 8;       // Frame delay to switch between animation frames
int frameCounter = 0;     // General frames counter
int score = 0;
//----------------------------------------------------------------------------------
// Types and Structures Definition
//----------------------------------------------------------------------------------
struct Sounds
{
    Sound mySound;
} mosik, hitsound, kuso;

struct Arrow
{
    Vector2 position;
    Vector2 positionStatic;
    Vector2 positionStaticBottom;
    int speed;
    bool active = true;
    Texture2D texture;
    Texture2D textureStatic;
} ArrowUp, ArrowDown, ArrowLeft, ArrowRight;

struct Textures
{
    Vector2 position;
    Texture2D texture;
} Pepe, PepeDos, girl, healthbarTexture;

struct Images
{
    Image image;
    Image imageStatic;
} PepeImg, PepeDosImg, ArrowDownImg, ArrowUpImg, ArrowLeftImg, ArrowRightImg, healthbarImg;

struct OriginalArrowSize
{
    Vector2 size;
} ArrowUpSize;

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
static void InitGame(void);        // Initialize game
static void UpdateGame(void);      // Update game (one frame)
static void DrawGame(void);        // Draw game (one frame)
static void UnloadGame(void);      // Unload game
static void UpdateDrawFrame(void); // Update and Draw (one frame)

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization

    //-------------------------------------------------------------------------------------------------------
    InitWindow(screenWidth, screenHeight, "DDDance!!!");
    InitGame();
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update and Draw
        //-------------------------------------------------------------------------------------------------------
        UpdateDrawFrame();
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadGame();
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

//------------------------------------------------------------------------------------
// Module Functions Definitions (local)
//------------------------------------------------------------------------------------
void InitGame(void)
{
    InitAudioDevice();

    // Initialize music/sounds
    mosik.mySound = LoadSound("Source\\resources\\awo.wav");
    kuso.mySound = LoadSound("Source\\resources\\kuso.wav");
    hitsound.mySound = LoadSound("Source\\resources\\hitSound.wav");

    // Initialize textures/images
    PepeImg.image = LoadImageAnim("Source\\resources\\mosik.gif", &animFrames);
    PepeDosImg.image = LoadImageAnim("Source\\resources\\mosikDos.gif", &animFrames);

    healthbarImg.image = LoadImage("Source\\resources\\healthbar.png");
    healthbarTexture.texture = LoadTextureFromImage(healthbarImg.image);
    healthbarTexture.position.x = 1000;
    healthbarTexture.position.y = 20;

    Pepe.texture = LoadTextureFromImage(PepeImg.image);
    PepeDos.texture = LoadTextureFromImage(PepeDosImg.image);

    girl.texture = LoadTexture("Source\\resources\\audacity.png");

    // experimental arrow
    ArrowDownImg.image = LoadImage("Source\\resources\\arrowDown.png");
    ArrowDown.texture = LoadTextureFromImage(ArrowDownImg.image);
    ArrowDown.textureStatic = LoadTextureFromImage(ArrowDownImg.image);
    ArrowDown.position.x = 180;
    ArrowDown.position.y = 10;
    ArrowDown.speed = 5;
    ArrowDown.positionStatic.y = 10;
    ArrowDown.positionStatic.x = 180;
    ArrowDown.positionStaticBottom.y = 760;
    ArrowDown.positionStaticBottom.x = 180;

    ArrowUpImg.image = LoadImage("Source\\resources\\arrowUp.png");
    ArrowUpImg.imageStatic = LoadImage("Source\\resources\\arrowUpClicked.png");
    ArrowUp.texture = LoadTextureFromImage(ArrowUpImg.image);
    ArrowUp.textureStatic = LoadTextureFromImage(ArrowUpImg.image);
    ArrowUp.position.x = 240;
    ArrowUp.position.y = 10;
    ArrowUp.speed = 5;
    ArrowUp.positionStatic.y = 10;
    ArrowUp.positionStatic.x = 240;
    ArrowUp.positionStaticBottom.y = 760;
    ArrowUp.positionStaticBottom.x = 240;
    ArrowUpSize.size.x = ArrowUpImg.imageStatic.width;
    ArrowUpSize.size.y = ArrowUpImg.imageStatic.height;

    ArrowLeftImg.image = LoadImage("Source\\resources\\arrowLeft.png");
    ArrowLeft.texture = LoadTextureFromImage(ArrowLeftImg.image);
    ArrowRight.textureStatic = LoadTextureFromImage(ArrowLeftImg.image);
    ArrowLeft.position.x = 120;
    ArrowLeft.position.y = 10;
    ArrowLeft.speed = 5;
    ArrowLeft.positionStatic.y = 10;
    ArrowLeft.positionStatic.x = 120;
    ArrowLeft.positionStaticBottom.y = 760;
    ArrowLeft.positionStaticBottom.x = 120;

    ArrowRightImg.image = LoadImage("Source\\resources\\arrowRight.png");
    ArrowRight.texture = LoadTextureFromImage(ArrowRightImg.image);
    ArrowRight.textureStatic = LoadTextureFromImage(ArrowRightImg.image);
    ArrowRight.position.x = 300;
    ArrowRight.position.y = 10;
    ArrowRight.speed = 5;
    ArrowRight.positionStatic.y = 10;
    ArrowRight.positionStatic.x = 300;
    ArrowRight.positionStaticBottom.y = 760;
    ArrowRight.positionStaticBottom.x = 300;

    // arrowsVector.push_back(ArrowLeft);
    // arrowsVector.push_back(ArrowUp);
    // arrowsVector.push_back(ArrowDown);
    // arrowsVector.push_back(ArrowRight);

    // std::cout << arrowsVector.size();
    // ArrowDown.texture = LoadTexture("Source\\resources\\arrowDown.png");
    // Image arrowDownImg = LoadImage("Source\\resources\\arrowDown.png"); // NOT WORKING
    // ArrowUp.texture = LoadTexture("Source\\resources\\arrowUp.png");
    // ArrowLeft.texture = LoadTexture("Source\\resources\\arrowLeft.png");
    // ArrowRight.texture = LoadTexture("Source\\resources\\arrowRight.png");
}

// Update game (one frame)
void UpdateGame(void)
{

    frameCounter++;
    if (frameCounter >= frameDelay)
    {
        currentAnimFrame++;
        if (currentAnimFrame >= animFrames)
            currentAnimFrame = 0;

        nextFrameDataOffset = PepeImg.image.width * PepeImg.image.height * 4 * currentAnimFrame;
        UpdateTexture(Pepe.texture, ((unsigned char *)PepeImg.image.data) + nextFrameDataOffset);
        nextFrameDataOffset = PepeDosImg.image.width * PepeDosImg.image.height * 4 * currentAnimFrame;
        UpdateTexture(PepeDos.texture, ((unsigned char *)PepeDosImg.image.data) + nextFrameDataOffset);

        frameCounter = 0;
    }

    // to be fixed later
    // for (unsigned i = 0; i < arrowsVector.size(); ++i)
    // {
    //     std::cout << arrowsVector[i].position.y;
    //     arrowsVector[i].position.y += arrowsVector[i].speed.y;

    //     if (arrowsVector[i].position.y >= 850)
    //     {
    //         arrowsVector[i].position.y = 0;
    //         arrowsVector[i].speed.y = GetRandomValue(0, 15);
    //     }
    // }

    ArrowDown.position.y += ArrowDown.speed;
    ArrowUp.position.y += ArrowUp.speed;
    ArrowLeft.position.y += ArrowLeft.speed;
    ArrowRight.position.y += ArrowRight.speed;

    if (ArrowDown.position.y >= 790)
    {
        ArrowDown.position.y = 10;
        ArrowDown.speed = GetRandomValue(5, 15);
    }
    if (ArrowUp.position.y >= 790)
    {
        ArrowUp.position.y = 10;
        ArrowUp.speed = GetRandomValue(5, 15);
    }
    if (ArrowLeft.position.y >= 790)
    {
        ArrowLeft.position.y = 10;
        ArrowLeft.speed = GetRandomValue(5, 15);
    }
    if (ArrowRight.position.y >= 790)
    {
        ArrowRight.position.y = 10;
        ArrowRight.speed = GetRandomValue(5, 15);
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
        IsSoundPlaying(mosik.mySound) ? PauseSound(mosik.mySound) : PlaySound(mosik.mySound);
    };

    // do something when we press W S A D keys
    if (IsKeyPressed(KEY_W))
    {
        if (ArrowUp.position.y >= 700 && ArrowUp.position.y <= 800)
        {
            PlaySound(hitsound.mySound);
            score++;
        }
        else
        {
            PlaySound(kuso.mySound);
        }
    }
    if (IsKeyPressed(KEY_S))
    {
        if (ArrowDown.position.y >= 700 && ArrowDown.position.y <= 800)
        {
            PlaySound(hitsound.mySound);
            score++;
        }
        else
        {
            PlaySound(kuso.mySound);
        }
    }
    if (IsKeyPressed(KEY_A))
    {
        if (ArrowLeft.position.y >= 700 && ArrowLeft.position.y <= 800)
        {
            PlaySound(hitsound.mySound);
            score++;
        }
        else
        {
            PlaySound(kuso.mySound);
        }
    }
    if (IsKeyPressed(KEY_D))
    {
        if (ArrowRight.position.y >= 700 && ArrowRight.position.y <= 800)
        {
            PlaySound(hitsound.mySound);
            score++;
        }
        else
        {
            PlaySound(kuso.mySound);
        }
    }
    if (IsKeyPressed(KEY_K))
    {

        PlaySound(kuso.mySound);
    }
}

// Draw game (one frame)
void DrawGame(void)
{
    BeginDrawing();
    ClearBackground(WHITE);

    IsSoundPlaying(mosik.mySound) ? DrawText("Press SPACE to PAUSE MOSIK!", 400, 180, 30, BLACK) : DrawText("Press SPACE to PLAY MOSIK!", 400, 180, 30, BLACK);
    DrawText("Press K to PLAY KUSO!", 400, 120, 30, BLACK);

    // DrawTexture(girl.texture, -300, 0, WHITE);
    DrawText(TextFormat("Score: %i", score), 1050, 90, 30, BLACK);
    DrawText("Press LEFT to make PEPE DANCE FASTER!", 700, 700, 30, BLACK);

    DrawText("Press RIGHT to make PEPE DANCE SLOWER!", 700, 800, 30, BLACK);

    DrawTexture(Pepe.texture, 700, 400, WHITE);
    DrawTexture(PepeDos.texture, 1000, 200, WHITE);

    DrawRectangle(60, 10, 330, 50, Color{0, 0, 125, 150});

    DrawRectangle(100, 60, 250, 670, Color{0, 0, 255, 50});

    DrawRectangle(80, 730, 300, 100, Color{0, 0, 255, 150});

    DrawRectangle(1050, 30, 267, 50, Color{180, 8, 8, 150});

    // experimental arrow
    DrawTexture(ArrowDown.texture, ArrowDown.position.x, ArrowDown.position.y, BLACK);
    DrawTexture(ArrowDown.texture, ArrowDown.positionStatic.x, ArrowDown.positionStatic.y, BLACK);
    DrawTexture(ArrowDown.texture, ArrowDown.positionStaticBottom.x, ArrowDown.positionStaticBottom.y, Color{255, 255, 236, 255});

    DrawTexture(ArrowUp.texture, ArrowUp.position.x, ArrowUp.position.y, BLACK);
    DrawTexture(ArrowUp.texture, ArrowUp.positionStatic.x, ArrowUp.positionStatic.y, BLACK);
    DrawTexture(ArrowUp.textureStatic, ArrowUp.positionStaticBottom.x, ArrowUp.positionStaticBottom.y, Color{255, 255, 236, 255});

    DrawTexture(ArrowLeft.texture, ArrowLeft.position.x, ArrowLeft.position.y, BLACK);
    DrawTexture(ArrowLeft.texture, ArrowLeft.positionStatic.x, ArrowLeft.positionStatic.y, BLACK);
    DrawTexture(ArrowLeft.texture, ArrowLeft.positionStaticBottom.x, ArrowLeft.positionStaticBottom.y, Color{255, 255, 236, 255});

    DrawTexture(ArrowRight.texture, ArrowRight.position.x, ArrowRight.position.y, BLACK);
    DrawTexture(ArrowRight.texture, ArrowRight.positionStatic.x, ArrowRight.positionStatic.y, BLACK);
    DrawTexture(ArrowRight.texture, ArrowRight.positionStaticBottom.x, ArrowRight.positionStaticBottom.y, Color{255, 255, 236, 255});

    DrawTexture(healthbarTexture.texture, healthbarTexture.position.x, healthbarTexture.position.y, WHITE);

    EndDrawing();
}

// Unload game variables
void UnloadGame(void)
{
    UnloadSound(mosik.mySound);     // Unload sound data
    CloseAudioDevice();             // Close audio device
    UnloadTexture(Pepe.texture);    // Unload texture
    UnloadImage(PepeImg.image);     // Unload image (contains all frames)
    UnloadTexture(PepeDos.texture); // Unload texture
    UnloadImage(PepeDosImg.image);  // Unload image (contains all frames)
    UnloadImage(ArrowDownImg.image);
    UnloadImage(ArrowLeftImg.image);
    UnloadImage(ArrowRightImg.image);
    UnloadImage(ArrowUpImg.image);
    UnloadTexture(ArrowDown.texture);
    UnloadTexture(ArrowUp.texture);
    UnloadTexture(ArrowLeft.texture);
    UnloadTexture(ArrowRight.texture);
    UnloadImage(healthbarImg.image);
    UnloadTexture(healthbarTexture.texture);
}

// Update and Draw (one frame)
void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}
