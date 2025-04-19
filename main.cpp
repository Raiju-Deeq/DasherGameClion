#include "raylib.h"

struct AnimData
{
    Rectangle rec;
    Vector2 pos;
    int frame;
    float updateTime;
    float runningTime;
};

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
        nebulae[i].pos.x = windowDimensions[i] + i * 300; // Set the initial X position of the first nebula hazard
    }

    while (!WindowShouldClose())
    {
        const float deltaTime = GetFrameTime(); // Get the time between frames
        BeginDrawing (); // Start drawing
        ClearBackground (WHITE);
        DrawText ("Dasher Game", 0, 0, 15, BLACK);
        DrawText ("Press ESC to exit", 0, 20, 10, BLACK);
        DrawText ("Press SPACE to jump", 0, 40, 10, BLACK);

        //Update Scarfy animation
        if (!isAirborne) {
            scarfyData.runningTime += deltaTime; // Update the running time
            if (scarfyData.runningTime >= scarfyData.updateTime)
            {
                scarfyData.runningTime = 0.0f; // Reset the running time
                // updated animation frame
                scarfyData.rec.x = scarfyData.frame * scarfyData.rec.width; // Update the X position of the rectangle based on the frame
                scarfyData.frame++; // Increment the frame
                if (scarfyData.frame > 5) // Check if the frame is greater than 5
                {
                    scarfyData.frame = 0; // Reset the frame to 0
                }
            }
        }

        // Update nebula animation
        for (int i = 0; i < sizeOfNebula; i++)
        {
            nebulae[i].runningTime += deltaTime; // Update the running time
            if (nebulae[i].runningTime >= nebulae[i].updateTime)
            {
                nebulae[i].runningTime = 0.0f; // Reset the running time
                // updated animation frame
                nebulae[i].rec.x = nebulae[i].frame * nebulae[i].rec.width; // Update the X position of the rectangle based on the frame
                nebulae[i].frame++; // Increment the frame
                if (nebulae[i].frame > 7) // Check if the frame is greater than 7
                {
                    nebulae[i].frame = 0; // Reset the frame to 0
                }
            }
        }

        scarfyData.pos.y += velocity * deltaTime; // Update scarfy position

        for (int i = 0; i < sizeOfNebula; i++)
        {
            nebulae[i].pos.x += nebVelocity * deltaTime; // Update the nebula position
        }


        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, RED); // Draw the scarfy character

        for (int i =0; i <sizeOfNebula; i++)
        {
            DrawTextureRec(nebula, nebulae[i].rec, nebulae[i].pos, ORANGE); // Draw the nebula hazard
        }

        if (IsKeyPressed(KEY_SPACE) && !isAirborne) // Check if the space key is pressed
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
    CloseWindow ();
}