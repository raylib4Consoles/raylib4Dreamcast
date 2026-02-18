/*******************************************************************************************
*
*   raylib [audio] example - music stream
*
*   Example complexity rating: [★☆☆☆] 1/4
*
*   Example originally created with raylib 1.3, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2015-2025 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include <raylib.h>

#define ATTR_DREAMCAST_WIDTH 640
#define ATTR_DREAMDAST_HEIGHT 480

static bool done = false;
static bool paused = false;
static bool restart = false;
static bool dpadDownDown;
static bool dpadUpDown;

static void updateController(void) 
{
    
    bool startPressed;
    bool aPressed;
    bool xPressed;

    if(!IsGamepadAvailable(0))
        return;

    dpadDownDown = IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_DOWN);
    dpadUpDown = IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP);
    startPressed = IsGamepadButtonPressed(0, GAMEPAD_BUTTON_MIDDLE_RIGHT);
    aPressed = IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_DOWN);
    xPressed = IsGamepadButtonPressed(0, GAMEPAD_BUTTON_RIGHT_FACE_LEFT);

    if(startPressed)
        done = true;

    
    if(aPressed) 
        paused = true;

    if(xPressed) 
        restart = true;
}
//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = ATTR_DREAMCAST_WIDTH;
    const int screenHeight = ATTR_DREAMDAST_HEIGHT;

    InitWindow(screenWidth, screenHeight, "raylib [audio] example - music stream");

    InitAudioDevice();              // Initialize audio device

    Music music = LoadMusicStream("/rd/country.mp3");

    PlayMusicStream(music);

    float timePlayed = 0.0f;        // Time played normalized [0.0f..1.0f]
    bool pause = false;             // Music playing paused

    SetTargetFPS(30);               // Set our game to run at 30 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!done)    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        UpdateMusicStream(music);   // Update music buffer with new stream data
        updateController();
        // Restart music playing (stop and play)
        if (restart)
        {
            StopMusicStream(music);
            PlayMusicStream(music);
            restart=false;
        }

        // Pause/Resume music playing
        if (paused)
        {
            paused=false;
            pause = !pause;

            if (pause) PauseMusicStream(music);
            else ResumeMusicStream(music);
        }

        // Get normalized time played for current music stream
        timePlayed = GetMusicTimePlayed(music)/GetMusicTimeLength(music);

        if (timePlayed > 1.0f) timePlayed = 1.0f;   // Make sure time played is no longer than music
        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("MUSIC SHOULD BE PLAYING!", 175, 150, 20, BLACK);

            DrawRectangle(120, 200, 400, 12, BLACK);
            DrawRectangle(120, 200, (int)(timePlayed*400.0f), 12, MAROON);
            DrawRectangleLines(120, 200, 400, 12, BLACK);

            DrawText("PRESS X TO RESTART MUSIC", 165, 250, 20, BLACK);
            DrawText("PRESS A TO PAUSE/RESUME MUSIC", 128, 280, 20, BLACK);

        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadMusicStream(music);   // Unload music stream buffers from RAM

    CloseAudioDevice();         // Close audio device (music streaming is automatically stopped)

    CloseWindow();              // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
