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
    // Initialize the window
    const int windowWidth {800}; // Set the width of the window
    const int windowHeight {600}; // Set the height of the window
    InitWindow (windowWidth,windowHeight, "Dasher Game");
    SetTargetFPS (60);


    int velocity{0}; // Set the initial velocity of the rectangle
    bool isAirborne{false}; // Set the initial state of jumping to false
    int gravity{1'000}; // Set the gravity value (in pixels per second)
    int jumpHeight{600}; // Set the jump height (In pixels per second)


    // Scarfy variables
    Texture2D scarfy = LoadTexture("textures/scarfy.png"); // Load the texture for the scarfy character
    // Create a rectangle for the scarfy character
    AnimData scarfyData; // Create a struct for the scarfy character
    scarfyData.rec.width = scarfy.width/6; // Set the width of the rectangle based on the texture width
    scarfyData.rec.height = scarfy.height; // Set the height of the rectangle based on the texture height
    scarfyData.rec.x = 0; // Set the initial X position of the rectangle
    scarfyData.rec.y = 0; // Set the initial Y position of the rectangle
    scarfyData.pos.x = windowWidth/5 - scarfyData.rec.width/5; // Set the initial X position of the scarfy character
    scarfyData.pos.y = windowHeight - scarfyData.rec.height; // Set the initial Y position of the scarfy character
    scarfyData.frame = 0;
    scarfyData.updateTime = 1.f/12.f; // Set the time between frames (12 frames per second)
    scarfyData.runningTime = 0.0f; // Set the initial running time of the animation

    // Load the texture for nebula hazard
    Texture2D nebula = LoadTexture("textures/12_nebula_spritesheet.png"); // Load the texture for the nebula hazard

    int nebVelocity{-600}; // Set the initial velocity of the nebula hazard
    // AnimData struct for nebula
    AnimData nebData{
            {0.f, 0.f, (float)nebula.width/8, (float)nebula.height/8}, // Set the rectangle for the nebula hazard
            {windowWidth, (float)windowWidth - nebula.height/8}, // Set the initial position of the nebula hazard
            0, // Set the initial frame of the nebula animation
            {1.f/12.f}, // Set the time between frames (12 frames per second)
            0 // Set the initial running time of the nebula animation
        };

    // AnimData struct for nebula2
    AnimData nebData2{
                {0.f, 0.f, (float)nebula.width/8, (float)nebula.height/8}, // Set the rectangle for the nebula hazard
                {windowWidth +300, (float)windowWidth - nebula.height/8}, // Set the initial position of the nebula hazard
                0, // Set the initial frame of the nebula animation
                {1.f/16.f}, // Set the time between frames (12 frames per second)
                0 // Set the initial running time of the nebula animation
            };


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
        nebData.runningTime += deltaTime; // Update the running time
        if (nebData.runningTime>= nebData.updateTime)
        {
            nebData.runningTime = 0.0f; // Reset the running time
            // updated animation frame
            nebData.rec.x = nebData.frame * nebData.rec.width; // Update the X position of the rectangle based on the frame
            nebData.frame++; // Increment the frame
            if (nebData.frame > 7) // Check if the frame is greater than 7
            {
                nebData.frame = 0; // Reset the frame to 0
            }
        }

        // Update nebula2 animation
        nebData2.runningTime += deltaTime; // Update the running time
        if (nebData2.runningTime>= nebData2.updateTime)
        {
            nebData2.runningTime = 0.0f; // Reset the running time
            // updated animation frame
            nebData2.rec.x = nebData2.frame * nebData2.rec.width; // Update the X position of the rectangle based on the frame
            nebData2.frame; // Increment the frame
            if (nebData2.frame > 7) // Check if the frame is greater than 7
            {
                nebData2.frame = 0; // Reset the frame to 0
            }
        }


        scarfyData.pos.y += velocity * deltaTime; // Update scarfy position
        nebData.pos.x += nebVelocity * deltaTime; // Update the nebula position
        nebData2.pos.x += nebVelocity * deltaTime; // Update the second nebula position

        DrawTextureRec(scarfy, scarfyData.rec, scarfyData.pos, RED); // Draw the scarfy character
        DrawTextureRec(nebula, nebData.rec, nebData2.pos, WHITE); // Draw the nebula hazard
        DrawTextureRec(nebula, nebData2.rec, nebData2.pos, PURPLE); // Draw the second nebula hazard

        if (IsKeyPressed(KEY_SPACE) && !isAirborne) // Check if the space key is pressed
        {
            velocity = -jumpHeight; // Set the velocity when space is pressed
        }
        else if (scarfyData.pos.y < windowHeight - scarfyData.rec.height) // Check if the rectangle is not on the ground
        {
            velocity += gravity * deltaTime; // Increase the velocity to simulate gravity
            isAirborne = true; // Set the airborne state to true
        }
        else // If the rectangle is on the ground
        {
            velocity = 0; // Set the velocity to 0
            scarfyData.pos.y = windowHeight - scarfyData.rec.height; // Reset the Y position of the rectangle to the ground level
            isAirborne = false; // Set the airborne state to false
        }


        EndDrawing (); // End drawing
    }
    UnloadTexture (scarfy); // Unload the texture for the scarfy character
    UnloadTexture (nebula); // Unload the texture for the nebula hazard
    CloseWindow ();
}