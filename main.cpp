#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

bool isOnGround(AnimData data, int windowHeight)
{
    return data.pos.y >= windowHeight - data.rec.height;
}

AnimData updateAnimData(AnimData data, float deltaTime, int maxFrame)
{
    // Update the running time
    data.runningTime += deltaTime;
    if (data.runningTime >= data.updateTime)
    {
        data.runningTime = 0.0f;
        // Update the animation frame
        data.rec.x = data.frame * data.rec.width;
        data.frame++;
        if (data.frame > maxFrame)
        {
            data.frame = 0;
        }
    }
    return data;
}

int main()
{
    // Array of integers to store window dimensions
    int windowDimensions[2];
    windowDimensions[0] = 800; // Set the width of the window
    windowDimensions[1] = 600; // Set the height of the window

    // Initialize the window
    InitWindow (windowDimensions[0], windowDimensions[1], "Dasher Game");
    SetTargetFPS (60);

    // Scarfy variables
    int velocity{0}; // Set the initial velocity of the rectangle
    bool isAirborne{false}; // Set the initial state of jumping to false
    int gravity{1'000}; // Set the gravity value (in pixels per second)
    int jumpHeight{600}; // Set the jump height (In pixels per second)

    Texture2D background = LoadTexture("textures/far-buildings.png"); // Load the background texture
    float bgX{}; // Set the initial X position of the background

    Texture2D midground = LoadTexture("textures/back-buildings.png"); // Load the midground texture
    float mgX{}; // Set the initial X position of the midground

    Texture2D foreground = LoadTexture("textures/foreground.png"); // Load the foreground texture
    float fgX{}; // Set the initial X position of the foreground



    Texture2D scarfy = LoadTexture("textures/scarfy.png"); // Load the texture for the scarfy character
    // Create a rectangle for the scarfy character
    AnimData scarfyData; // Create a struct for the scarfy character
    scarfyData.rec.width = scarfy.width/6; // Set the width of the rectangle based on the texture width
    scarfyData.rec.height = scarfy.height; // Set the height of the rectangle based on the texture height
    scarfyData.rec.x = 0; // Set the initial X position of the rectangle
    scarfyData.rec.y = 0; // Set the initial Y position of the rectangle
    scarfyData.pos.x = windowDimensions[0]/5 - scarfyData.rec.width/5; // Set the initial X position of the scarfy character
    scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height; // Set the initial Y position of the scarfy character
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.f/12.f; // Set the time between frames (12 frames per second)
    scarfyData.runningTime = 0.0f; // Set the initial running time of the animation

    // Load the texture for nebula hazard
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png"); // Load the texture for the nebula hazard


    int nebVelocity{-600}; // Set the initial velocity of the nebula hazard


    const int sizeOfNebula = 6; // Set the size of the nebula array
    AnimData nebulae[sizeOfNebula]{}; // Create an array of AnimData structs for the nebula hazards

    for (int i = 0; i < sizeOfNebula; i++)
    {
        nebulae[i].rec.x = 0.f;
        nebulae[i].rec.y = 0.f;
        nebulae[i].rec.width = nebula.width/8.f;
        nebulae[i].rec.height = nebula.height/8.f;
        nebulae[i].pos.y = windowDimensions[1] - nebula.height/8.f;
        nebulae[i].frame = 0;
        nebulae[i].runningTime = 0.0f;
        nebulae[i].updateTime = 1.f/16.f; // Set the time between frames (16 frames per second)
        nebulae[i].pos.x = windowDimensions[0] + i * 300; // Set the initial X position of the first nebula hazard
    }

    float finishLine { nebulae[sizeOfNebula -1 ].pos.x}; // Set the finish line position based on the last nebula hazard

    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime(); // Get the time between frames
        BeginDrawing (); // Start drawing
        ClearBackground (WHITE);

        bgX -= 20 * deltaTime; // Update the X position of the background
        if (bgX < -background.width * 3.5f) // Check if the background is off the screen
        {
            bgX = 0.f; // Reset the X position of the background
        }

        mgX -= 40 * deltaTime; // Update the X position of the midground
        if (mgX < -midground.width * 3.5f) // Check if the midground is off the screen
        {
            mgX = 0.f; // Reset the X position of the midground
        }

        fgX -= 80 * deltaTime; // Update the X position of the foreground
        if (fgX < -foreground.width * 3.5f) // Check if the foreground is off the screen
        {
            fgX = 0.f; // Reset the X position of the foreground
        }

        // Draw the background
        Vector2 bg1Pos{bgX, 0.f}; // Set the initial position of the background
        DrawTextureEx(background,bg1Pos,0.f,3.5f,WHITE); // Draw the background texture
        Vector2 bg2Pos{bgX + background.width * 3.5f, 0.f}; // Set the position of the second background
        DrawTextureEx(background,bg2Pos,0.f,3.5f,WHITE); // Draw the second background texture

        Vector2 mg1Pos{mgX, 0.f}; // Set the initial position of the midground
        DrawTextureEx(midground,mg1Pos,0.f,3.5f,WHITE); // Draw the midground texture
        Vector2 mg2Pos{mgX + midground.width * 3.5f, 0.f}; // Set the position of the second midground
        DrawTextureEx(midground,mg2Pos,0.f,3.5f,WHITE); // Draw the second midground texture

        Vector2 fg1Pos{fgX, 0.f}; // Set the initial position of the foreground
        DrawTextureEx(foreground,fg1Pos,0.f,3.5f,WHITE); // Draw the foreground texture
        Vector2 fg2Pos{fgX + foreground.width * 3.5f, 0.f}; // Set the position of the second foreground
        DrawTextureEx(foreground,fg2Pos,0.f,3.5f,WHITE); // Draw the second foreground texture

        // Draw the text
        DrawText ("Dasher Game", 0, 0, 15, BLACK);
        DrawText ("Press ESC to exit", 0, 20, 10, BLACK);
        DrawText ("Press SPACE to jump", 0, 40, 10, BLACK);

        //Update Scarfy animation
        if (!isAirborne)
        {
            scarfyData = updateAnimData(scarfyData, deltaTime, 5); // Update the animation data
        }

        // Update nebula animation
        for (int i = 0; i < sizeOfNebula; i++)
        {
            nebulae[i] = updateAnimData(nebulae[i], deltaTime, 7); // Update the animation data
        }

        scarfyData.pos.y += velocity * deltaTime; // Update scarfy position

        for (int i = 0; i < sizeOfNebula; i++)
        {
            nebulae[i].pos.x += nebVelocity * deltaTime; // Update the nebula position
        }

        finishLine += nebVelocity * deltaTime; // Update the finish line position

        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, BLUE); // Draw the scarfy character

        for (int i =0; i <sizeOfNebula; i++)
        {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, ORANGE); // Draw the nebula hazard
        }

        if (IsKeyPressed(KEY_SPACE) && (isOnGround(scarfyData, windowDimensions[1]))) // Check if the space key is pressed
        {
            velocity = -jumpHeight; // Set the velocity when space is pressed
        }
        else if (scarfyData.pos.y < windowDimensions[1] - scarfyData.rec.height) // Check if the rectangle is not on the ground
        {
            velocity += gravity * deltaTime; // Increase the velocity to simulate gravity
            isAirborne = true; // Set the airborne state to true
        }
        else // If the rectangle is on the ground
        {
            velocity = 0; // Set the velocity to 0
            scarfyData.pos.y = windowDimensions[1] - scarfyData.rec.height; // Reset the Y position of the rectangle to the ground level
            isAirborne = false; // Set the airborne state to false
        }


        EndDrawing (); // End drawing
    }
    UnloadTexture (scarfy); // Unload the texture for the scarfy character
    UnloadTexture (nebula); // Unload the texture for the nebula hazard
    UnloadTexture (background); // Unload the background texture
    UnloadTexture (midground); // Unload the midground texture
    UnloadTexture (foreground); // Unload the foreground texture
    CloseWindow ();
}