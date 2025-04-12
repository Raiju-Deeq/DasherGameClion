#include "raylib.h"

int main()
{
    const int windowWidth {800}; // Set the width of the window
    const int windowHeight {600}; // Set the height of the window
    InitWindow (windowWidth,windowHeight, "Dasher Game");

    int velocity{0}; // Set the initial velocity of the rectangle
    bool isAirborne{false}; // Set the initial state of jumping to false
    int gravity{1'000}; // Set the gravity value (in pixels per second)
    int jumpHeight{600}; // Set the jump height (In pixels per second)


    // Load the texture for nebula hazard
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png"); // Load the texture for the nebula hazard
    Rectangle nebRec{0.0f, 0.0f, (float)nebula.width/8,(float)nebula.height/8}; // Create a rectangle for the nebula hazard
    Vector2 nebPos{windowWidth, windowHeight - nebRec.height}; // Set the initial position of the nebula hazard
    int nebVelocity{-600}; // Set the initial velocity of the nebula hazard
    // Nebula animation variables
    int nebFrame{}; // Set the initial frame of the nebula animation
    const float nebUpdateTime{1.f/12.f}; // Set the time between frames (12 frames per second)
    float nebRunningTime{}; // Set the initial running time of the nebula animation






    // Load the texture for the scarfy character
    Texture2D scarfy = LoadTexture("textures/scarfy.png"); // Load the texture for the scarfy character
    Rectangle scarfyRec; // Create a rectangle for the scarfy character
    scarfyRec.width = scarfy.width/6;
    scarfyRec.height = scarfy.height;
    scarfyRec.x = 0; // Set the initial X position of the rectangle
    scarfyRec.y = 0; // Set the initial Y position of the rectangle
    Vector2 scarfyPos; // Create a vector for the position of the scarfy character
    scarfyPos.x = windowWidth/5 - scarfyRec.width/5; // Set the initial X position of the scarfy character
    scarfyPos.y = windowHeight - scarfyRec.height; // Set the initial Y position of the scarfy character


    // Animation variables
    int frame{}; // Set the initial frame of the animation
    const float updateTime{1.f/12.f}; // Set the time between frames (12 frames per second)
    float runningTime{}; // Set the initial running time of the animation




    SetTargetFPS (60);
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
            runningTime += deltaTime; // Update the running time
            if (runningTime >= updateTime)
            {
                runningTime = 0.0f; // Reset the running time
                // updated animation frame
                scarfyRec.x = frame * scarfyRec.width; // Update the X position of the rectangle based on the frame
                frame++; // Increment the frame
                if (frame > 5) // Check if the frame is greater than 5
                {
                    frame = 0; // Reset the frame to 0
                }
            }
        }

        // Update nebula animation
        nebRunningTime += deltaTime; // Update the running time
        if (nebRunningTime >= nebUpdateTime)
        {
            nebRunningTime = 0.0f; // Reset the running time
            // updated animation frame
            nebRec.x = nebFrame * nebRec.width; // Update the X position of the rectangle based on the frame
            nebFrame++; // Increment the frame
            if (nebFrame > 7) // Check if the frame is greater than 7
            {
                nebFrame = 0; // Reset the frame to 0
            }
        }

        scarfyPos.y += velocity * deltaTime; // Update scarfy position
        nebPos.x += nebVelocity * deltaTime; // Update the nebula position

        DrawTextureRec(scarfy, scarfyRec, scarfyPos, RED); // Draw the scarfy character
        DrawTextureRec(nebula, nebRec, nebPos, WHITE); // Draw the nebula hazard

        if (IsKeyPressed(KEY_SPACE) && !isAirborne) // Check if the space key is pressed
        {
            velocity = -jumpHeight; // Set the velocity when space is pressed
        }
        else if (scarfyPos.y < windowHeight - scarfyRec.height) // Check if the rectangle is not on the ground
        {
            velocity += gravity * deltaTime; // Increase the velocity to simulate gravity
            isAirborne = true; // Set the airborne state to true
        }
        else // If the rectangle is on the ground
        {
            velocity = 0; // Set the velocity to 0
            scarfyPos.y = windowHeight - scarfyRec.height; // Reset the Y position of the rectangle to the ground level
            isAirborne = false; // Set the airborne state to false
        }


        EndDrawing (); // End drawing
    }
    UnloadTexture (scarfy); // Unload the texture for the scarfy character
    UnloadTexture (nebula); // Unload the texture for the nebula hazard
    CloseWindow ();
}