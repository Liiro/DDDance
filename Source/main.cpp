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
#include "level.hpp"
#include <stack>
#include <string>
#include <cassert>

//----------------------------------------------------------------------------------
// Game State management
//----------------------------------------------------------------------------------
enum class State
{
    MAIN_MENU,
    GAME,
    END_GAME
};

std::stack<State> states;

void do_main_menu_frame()
{

    playbuttonImg.image = LoadImage("Source\\resources\\playbutton.png");
    playbuttonTexture.texture = LoadTextureFromImage(playbuttonImg.image);

    BeginDrawing();

    ClearBackground(Color{173, 216, 230});

    DrawTexture(playbuttonTexture.texture, 500, 180, WHITE);

    DrawText("Push Space To Play", 480, 560, 40, BLACK);

    EndDrawing();

    if (IsKeyPressed(KEY_SPACE))
    {
        InitGame();
        states.push(State::GAME);
    }

    if (IsKeyPressed(KEY_E))
    {
        UnloadGame();
        CloseWindow();
    }
}

void do_end_game_frame()
{
    int finalScore = declarationStruct.score;
    UnloadGame();
    InitGame();

    if (IsKeyPressed(KEY_SPACE))
    {
        states.push(State::GAME);
    }

    if (IsKeyPressed(KEY_ESCAPE))
    {
        states.pop();
    }

    if (IsKeyPressed(KEY_E))
    {
        CloseWindow();
    }

    replaybuttonImg.image = LoadImage("Source\\resources\\replaybutton.png");
    replaybuttonTexture.texture = LoadTextureFromImage(replaybuttonImg.image);

    BeginDrawing();
    ClearBackground(Color{173, 216, 230});

    DrawTexture(replaybuttonTexture.texture, 550, 250, WHITE);
    DrawText(TextFormat("Score: %i", finalScore), 1050, 90, 30, BLACK);

    DrawText("Push Space To Replay", 550, 550, 30, BLACK);

    EndDrawing();
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //-------------------------------------------------------------------------------------------------------
    InitWindow(declarationStruct.screenWidth, declarationStruct.screenHeight, "DDDance!!!");
    states.push(State::MAIN_MENU);
    SetTargetFPS(60); // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        // Update and Draw
        //-------------------------------------------------------------------------------------------------------
        State current_state = states.top();

        switch (current_state)
        {
        case State::MAIN_MENU:
            do_main_menu_frame();
            break;
        case State::GAME:
            UpdateDrawFrame();
            break;

        case State::END_GAME:
            do_end_game_frame();
            break;
        }
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadGame();
    CloseWindow(); // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}

// Initialize game (one frame)
void InitGame(void)
{
    InitAudioDevice();
    // Initialize music/sounds
    mosik.mySound = LoadSound("Source\\resources\\awo.wav");
    kuso.mySound = LoadSound("Source\\resources\\kuso.wav");
    hitsound.mySound = LoadSound("Source\\resources\\hitSound.wav");

    // Initialize textures/images
    PepeImg.image = LoadImageAnim("Source\\resources\\mosik.gif", &declarationStruct.animFrames);
    PepeDosImg.image = LoadImageAnim("Source\\resources\\mosikDos.gif", &declarationStruct.animFrames);

    healthbarImg.image = LoadImage("Source\\resources\\healthbar.png");
    healthbarTexture.texture = LoadTextureFromImage(healthbarImg.image);
    healthbarTexture.position.x = 1000;
    healthbarTexture.position.y = 20;

    Pepe.texture = LoadTextureFromImage(PepeImg.image);
    PepeDos.texture = LoadTextureFromImage(PepeDosImg.image);

    yellowImg.image = LoadImage("Source\\resources\\yellow.png");
    yellowTexture.texture = LoadTextureFromImage(yellowImg.image);

    blueImg.image = LoadImage("Source\\resources\\blue.png");
    blueTexture.texture = LoadTextureFromImage(blueImg.image);

    greenImg.image = LoadImage("Source\\resources\\green.png");
    greenTexture.texture = LoadTextureFromImage(greenImg.image);

    redImg.image = LoadImage("Source\\resources\\red.png");
    redTexture.texture = LoadTextureFromImage(redImg.image);

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

    hp1.width = 267;
    hp1.color = Color{238, 75, 43, 255};
    PlaySound(mosik.mySound);
}

// Update game (one frame)
void UpdateGame(void)
{
    colorfulCircie.yellow = false;
    colorfulCircie.red = false;
    colorfulCircie.blue = false;
    colorfulCircie.green = false;
    declarationStruct.frameCounter++;
    if (declarationStruct.frameCounter >= declarationStruct.frameDelay)
    {
        declarationStruct.currentAnimFrame++;
        if (declarationStruct.currentAnimFrame >= declarationStruct.animFrames)
            declarationStruct.currentAnimFrame = 0;

        declarationStruct.nextFrameDataOffset = PepeImg.image.width * PepeImg.image.height * 4 * declarationStruct.currentAnimFrame;
        UpdateTexture(Pepe.texture, ((unsigned char *)PepeImg.image.data) + declarationStruct.nextFrameDataOffset);
        declarationStruct.nextFrameDataOffset = PepeDosImg.image.width * PepeDosImg.image.height * 4 * declarationStruct.currentAnimFrame;
        UpdateTexture(PepeDos.texture, ((unsigned char *)PepeDosImg.image.data) + declarationStruct.nextFrameDataOffset);

        declarationStruct.frameCounter = 0;
    }

    if (IsSoundPlaying(mosik.mySound))
    {
        ArrowDown.position.y += ArrowDown.speed;
        ArrowUp.position.y += ArrowUp.speed;
        ArrowLeft.position.y += ArrowLeft.speed;
        ArrowRight.position.y += ArrowRight.speed;
        if (ArrowDown.position.y >= 790)
        {
            ArrowDown.position.y = 10;
            ArrowDown.speed = GetRandomValue(5, 8);
        }
        if (ArrowUp.position.y >= 790)
        {
            ArrowUp.position.y = 10;
            ArrowUp.speed = GetRandomValue(5, 8);
        }
        if (ArrowLeft.position.y >= 790)
        {
            ArrowLeft.position.y = 10;
            ArrowLeft.speed = GetRandomValue(5, 8);
        }
        if (ArrowRight.position.y >= 790)
        {
            ArrowRight.position.y = 10;
            ArrowRight.speed = GetRandomValue(5, 8);
        }
    }

    // control pepe speed
    if (IsKeyPressed(KEY_RIGHT))
        declarationStruct.frameDelay++;
    else if (IsKeyPressed(KEY_LEFT))
        declarationStruct.frameDelay--;
    if (declarationStruct.frameDelay > declarationStruct.MAX_FRAME_DELAY)
        declarationStruct.frameDelay = declarationStruct.MAX_FRAME_DELAY;
    else if (declarationStruct.frameDelay < declarationStruct.MIN_FRAME_DELAY)
        declarationStruct.frameDelay = declarationStruct.MIN_FRAME_DELAY;

    // control mosik playing status ON OFF
    if (IsKeyPressed(KEY_P))
    {
        IsSoundPlaying(mosik.mySound) ? PauseSound(mosik.mySound) : PlaySound(mosik.mySound);
    };

    // do something when we press W S A D keys
    if (IsKeyPressed(KEY_W))
    {
        if (ArrowUp.position.y >= 700 && ArrowUp.position.y <= 800)
        {
            colorfulCircie.blue = true;
            PlaySound(hitsound.mySound);
            declarationStruct.score++;
        }
        else
        {
            PlaySound(kuso.mySound);
            declarationStruct.misses--;
            hp1.width -= 10;
        }
    }
    if (IsKeyPressed(KEY_S))
    {
        if (ArrowDown.position.y >= 700 && ArrowDown.position.y <= 800)
        {
            colorfulCircie.yellow = true;
            PlaySound(hitsound.mySound);
            declarationStruct.score++;
        }
        else
        {
            PlaySound(kuso.mySound);
            declarationStruct.misses--;
            hp1.width -= 10;
        }
    }
    if (IsKeyPressed(KEY_A))
    {
        if (ArrowLeft.position.y >= 700 && ArrowLeft.position.y <= 800)
        {
            colorfulCircie.green = true;
            PlaySound(hitsound.mySound);
            declarationStruct.score++;
        }
        else
        {
            PlaySound(kuso.mySound);
            declarationStruct.misses--;
            hp1.width -= 10;
        }
    }
    if (IsKeyPressed(KEY_D))
    {
        if (ArrowRight.position.y >= 700 && ArrowRight.position.y <= 800)
        {
            colorfulCircie.red = true;
            PlaySound(hitsound.mySound);
            declarationStruct.score++;
        }
        else
        {
            PlaySound(kuso.mySound);
            declarationStruct.misses--;
            hp1.width -= 10;
        }
    }
    if (IsKeyPressed(KEY_K))
    {

        PlaySound(kuso.mySound);
        declarationStruct.misses--;
        hp1.width--;
    }
    if (hp1.width <= 0)
    {
        states.push(State::END_GAME);
    }
}

// Draw game (one frame)
void DrawGame(void)
{
    BeginDrawing();
    ClearBackground(WHITE);

    IsSoundPlaying(mosik.mySound) ? DrawText("Press P to PAUSE MOSIK!", 400, 180, 30, BLACK) : DrawText("Press P to PLAY MOSIK!", 400, 180, 30, BLACK);
    DrawText("Press K to PLAY KUSO!", 400, 120, 30, BLACK);

    // DrawTexture(girl.texture, -300, 0, WHITE);
    DrawText(TextFormat("Score: %i", declarationStruct.score), 1050, 90, 30, BLACK);
    DrawText("Press LEFT to make PEPE DANCE FASTER!", 700, 700, 30, BLACK);

    DrawText("Press RIGHT to make PEPE DANCE SLOWER!", 700, 800, 30, BLACK);

    DrawTexture(Pepe.texture, 700, 400, WHITE);
    DrawTexture(PepeDos.texture, 1000, 200, WHITE);

    DrawRectangle(60, 10, 330, 50, Color{0, 0, 125, 150});

    DrawRectangle(100, 60, 250, 670, Color{0, 0, 255, 50});

    DrawRectangle(80, 730, 300, 100, Color{0, 0, 255, 150});

    DrawRectangle(hp1.x, hp1.y, hp1.width, hp1.height, hp1.color); // blue

    if (colorfulCircie.yellow == true)
    {
        DrawTexture(yellowTexture.texture, 160, 740, WHITE);
    }
    if (colorfulCircie.green == true)
    {
        DrawTexture(greenTexture.texture, 100, 740, GREEN);
    }
    if (colorfulCircie.red == true)
    {
        DrawTexture(redTexture.texture, 280, 740, WHITE);
    }
    if (colorfulCircie.blue == true)
    {
        DrawTexture(blueTexture.texture, 220, 740, WHITE);
    }

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
    CloseAudioDevice();             // Close audio device
    UnloadSound(mosik.mySound);     // Unload sound data
    UnloadSound(kuso.mySound);      // Unload sound data
    UnloadSound(hitsound.mySound);  // Unload sound data
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
    UnloadImage(ArrowDownImg.imageStatic);
    UnloadImage(ArrowLeftImg.imageStatic);
    UnloadImage(ArrowRightImg.imageStatic);
    UnloadImage(ArrowUpImg.imageStatic);
    UnloadTexture(ArrowDown.textureStatic);
    UnloadTexture(ArrowUp.textureStatic);
    UnloadTexture(ArrowLeft.textureStatic);
    UnloadTexture(ArrowRight.textureStatic);
    UnloadImage(healthbarImg.image);
    UnloadTexture(healthbarTexture.texture);
    UnloadImage(yellowImg.image);
    UnloadTexture(yellowTexture.texture);
    UnloadImage(blueImg.image);
    UnloadTexture(blueTexture.texture);
    UnloadImage(greenImg.image);
    UnloadTexture(greenTexture.texture);
    UnloadImage(redImg.image);
    UnloadTexture(redTexture.texture);
    UnloadImage(playbuttonImg.image);
    UnloadTexture(playbuttonTexture.texture);
}

// Update and Draw (one frame)
void UpdateDrawFrame(void)
{
    UpdateGame();
    DrawGame();
}
