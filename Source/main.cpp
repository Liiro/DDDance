
#include "raylib.h"
#include <vector>
#include <list>
#include <algorithm>

constexpr int SPEED = 5;

struct vector2
{

    float x;
    float y;
};

//---------- Arrow ---------------------
class Arrow
{
public:
    vector2 position = {};
    vector2 direction = {};

    bool appear = false;

    virtual void render();
    virtual void update();

    virtual inline ~Arrow() = default;
};

void Arrow::render()
{

    // draw
    DrawCircle(position.x, position.y, 30, BLACK);
}

void Arrow::update()
{
}

class LEFT_ARROW : public Arrow
{

public:
    void update() override
    {

        position.y += direction.y * SPEED;
    }
};

class RIGHT_ARROW : public Arrow
{

public:
    void update() override
    {

        position.y += direction.y * SPEED;
    }
};

class UP_ARROW : public Arrow
{

public:
    void update() override
    {

        position.y += direction.y * SPEED;
    }
};

class DOWN_ARROW : public Arrow
{

public:
    void update() override
    {

        position.y += direction.y * SPEED;
    }
};

//---------- Level ---------------------

class Level
{
private:
    std::list<LEFT_ARROW> l_arrows = {};
    std::list<RIGHT_ARROW> r_arrows = {};
    std::list<UP_ARROW> u_arrows = {};
    std::list<DOWN_ARROW> d_arrows = {};

    std::vector<Arrow *> all_arrows = {};

public:
    void add_arrow(const LEFT_ARROW &l_a);
    void add_arrow(const RIGHT_ARROW &r_a);
    void add_arrow(const UP_ARROW &u_a);
    void add_arrow(const DOWN_ARROW &d_a);

    void remove_all_arrows();

    void init();
    void update();
    void render();
};

void Level::add_arrow(const LEFT_ARROW &l_a)
{
    l_arrows.push_back(l_a);
    all_arrows.push_back(&l_arrows.back());
}

void Level::add_arrow(const RIGHT_ARROW &r_a)
{
    r_arrows.push_back(r_a);
    all_arrows.push_back(&r_arrows.back());
}
void Level::add_arrow(const UP_ARROW &u_a)
{
    u_arrows.push_back(u_a);
    all_arrows.push_back(&u_arrows.back());
}
void Level::add_arrow(const DOWN_ARROW &d_a)
{
    d_arrows.push_back(d_a);
    all_arrows.push_back(&d_arrows.back());
}

void Level::remove_all_arrows()
{

    auto new_last_entity = std::remove_if(all_arrows.begin(), all_arrows.end(), [](const Arrow *a) -> bool
                                          { return a->appear; });
    all_arrows.erase(new_last_entity, all_arrows.end());

    l_arrows.remove_if([](const LEFT_ARROW &la) -> bool
                       { return la.appear; });
    r_arrows.remove_if([](const RIGHT_ARROW &ra) -> bool
                       { return ra.appear; });
    u_arrows.remove_if([](const UP_ARROW &ua) -> bool
                       { return ua.appear; });
    d_arrows.remove_if([](const DOWN_ARROW &da) -> bool
                       { return da.appear; });
}

void Level::init()
{
}

void Level::update()
{

    LEFT_ARROW la = {};
    la.position = {20, 0};
    la.direction = {0, 1};

    add_arrow(la);

    RIGHT_ARROW ra = {};
    ra.position = {60, 0};
    ra.direction = {0, 1};

    add_arrow(ra);

    UP_ARROW ua = {};
    ua.position = {100, 0};
    ua.direction = {0, 1};

    add_arrow(ua);

    DOWN_ARROW da = {};
    da.position = {140, 0};
    da.direction = {0, 1};

    add_arrow(da);

    for (Arrow *arrows : all_arrows)
    {
        arrows->update();
    }

    remove_all_arrows();
}

void Level::render()
{

    LEFT_ARROW la = {};
    la.position = {20, 0};
    la.direction = {0, 1};

    add_arrow(la);

    RIGHT_ARROW ra = {};
    ra.position = {60, 0};
    ra.direction = {0, 1};

    add_arrow(ra);

    UP_ARROW ua = {};
    ua.position = {100, 0};
    ua.direction = {0, 1};

    add_arrow(ua);

    DOWN_ARROW da = {};
    da.position = {140, 0};
    da.direction = {0, 1};

    add_arrow(da);

    for (Arrow *arrows : all_arrows)
    {
        arrows->render();
    }

    remove_all_arrows();
}

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    Level level;

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - basic window");

    SetTargetFPS(60); // Set our game to run at 60 frames-per-second

    level.init();

    // Main game loop
    while (!WindowShouldClose()) // Detect window close button or ESC key
    {
        level.update();

        BeginDrawing();
        level.render();

        ClearBackground(RAYWHITE);

        EndDrawing();
    }

    CloseWindow(); // Close window and OpenGL context

    return 0;
}