#pragma once

#include "raylib.h"
#include <string>
#include <cassert>

//----------------------------------------------------------------------------------
// Some Defines
//----------------------------------------------------------------------------------

//------------------------------------------------------------------------------------
// Global Variables Declaration
//------------------------------------------------------------------------------------

//----------------------------------------------------------------------------------
// Types and Structs
//----------------------------------------------------------------------------------
struct PositionsS
{
    int x = 0;
    int y = 0;
};

struct Sounds
{
    Sound mySound;
} mosik, hitsound, kuso;

struct declarations
{
    float CIRCLE_SPEED_PIXEL = 3.f;
    int CIRCLE_SIZE_PIXELS = 20;
    int screenWidth = 1400;
    int screenHeight = 850;
    int animFrames = 0;
    unsigned int nextFrameDataOffset = 0;
    int currentAnimFrame = 0;
    int frameDelay = 8;
    int frameCounter = 0;
    int score = 0;
    int MAX_FRAME_DELAY = 20;
    int MIN_FRAME_DELAY = 1;
    int misses = 0;

} declarationStruct;

struct Arrow
{
    PositionsS position = {.x = 0, .y = 0};
    PositionsS positionStatic = {.x = 0, .y = 0};
    PositionsS positionStaticBottom = {.x = 0, .y = 0};
    int speed = 5;
    bool active = true;
    Texture2D texture = {.id = 0,
                         .width = 0,
                         .height = 0,
                         .mipmaps = 0,
                         .format = 0};
    Texture2D textureStatic = {.id = 0,
                               .width = 0,
                               .height = 0,
                               .mipmaps = 0,
                               .format = 0};
    ;
} ArrowUp, ArrowDown, ArrowLeft, ArrowRight;

struct Textures
{
    PositionsS position = {.x = 0, .y = 0};
    Texture2D texture = {.id = 0,
                         .width = 0,
                         .height = 0,
                         .mipmaps = 0,
                         .format = 0};
    ;
} Pepe, PepeDos, healthbarTexture, yellowTexture, blueTexture, greenTexture, redTexture, playbuttonTexture, replaybuttonTexture;

struct Images
{
    Image image;
    Image imageStatic;
} PepeImg, PepeDosImg, ArrowDownImg, ArrowUpImg, ArrowLeftImg, ArrowRightImg, healthbarImg, yellowImg, blueImg, greenImg, redImg, playbuttonImg, replaybuttonImg;

struct OriginalArrowSize
{
    PositionsS size = {.x = 0, .y = 0};
} ArrowUpSize;

struct Rectangles
{
    int x = 1050;
    int y = 30;
    int width = 100;
    int height = 50;
    Color color = WHITE;
} hp1;

struct ColorfulCircles
{
    bool yellow = false;
    bool green = false;
    bool blue = false;
    bool red = false;
} colorfulCircie;

//------------------------------------------------------------------------------------
// Module Functions Declaration (local)
//------------------------------------------------------------------------------------
inline void InitGame(void);        // Initialize game
inline void UpdateGame(void);      // Update game (one frame)
inline void DrawGame(void);        // Draw game (one frame)
inline void UnloadGame(void);      // Unload game
inline void UpdateDrawFrame(void); // Update and Draw (one frame)