/*******************************************************************************************
*
*   raylib [core] example - 2d camera mouse zoom
*
*   Example originally created with raylib 4.2, last time updated with raylib 4.2
*
*   Example licensed under an unmodified zlib/libpng license, which is an OSI-certified,
*   BSD-like license that allows static linking with closed source software
*
*   Copyright (c) 2022-2024 Jeffery Myers (@JeffM2501)
*
********************************************************************************************/

#include "raylib.h"

#include "rlgl.h"
#include "raymath.h"

//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
int main ()
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "raylib [core] example - 2d camera mouse zoom");



    Font font = LoadFont("resources/fonts/alagard.png");

    Camera2D camera = { 0 };
    camera.zoom = 1.0f;

    Vector2 circlePos = {100,100}; // circle position
    float circleRadius = 50;



    SetTargetFPS(60);                   // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // Translate based on mouse right click


        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            Vector2 delta = GetMouseDelta();
            delta = Vector2Scale(delta, -1.0f/camera.zoom);

            camera.target = Vector2Add(camera.target, delta);
        }

        // Zoom based on mouse wheel
        float wheel = GetMouseWheelMove();
        if (wheel != 0)
        {
            // Get the world point that is under the mouse
            Vector2 mouseWorldPos = GetScreenToWorld2D(GetMousePosition(), camera);
            
            // Set the offset to where the mouse is
            camera.offset = GetMousePosition();

            // Set the target to match, so that the camera maps the world space point 
            // under the cursor to the screen space point under the cursor at any zoom
            camera.target = mouseWorldPos;

            // Zoom increment
            const float zoomIncrement = 0.125f;

            camera.zoom += (wheel*zoomIncrement);
            if (camera.zoom < zoomIncrement) camera.zoom = zoomIncrement;
        }

        const float moveSpeed = 5.0f;

        if(IsKeyDown(KEY_W))
        circlePos.y -= moveSpeed / camera.zoom;

        if(IsKeyDown(KEY_A))
        circlePos.x -= moveSpeed / camera.zoom;


        if(IsKeyDown(KEY_S))
        circlePos.y += moveSpeed / camera.zoom;

        if(IsKeyDown(KEY_D))
        circlePos.x += moveSpeed / camera.zoom;



        const float edgeOffset = 50.0f; // Distance from the edge to start moving camera
        if (circlePos.x - circleRadius < camera.target.x - screenWidth / 2 + edgeOffset)
            camera.target.x -= moveSpeed / camera.zoom;
        if (circlePos.x + circleRadius > camera.target.x + screenWidth / 2 - edgeOffset)
            camera.target.x += moveSpeed / camera.zoom ;
        if (circlePos.y - circleRadius < camera.target.y - screenHeight / 2 + edgeOffset)
            camera.target.y -= moveSpeed / camera.zoom;
        if (circlePos.y + circleRadius > camera.target.y + screenHeight / 2 - edgeOffset)
            camera.target.y += moveSpeed / camera.zoom;

        const char message[128] = "Kero";



        //----------------------------------------------------------------------------------

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
            ClearBackground(BLACK);

            


            BeginMode2D(camera);

                // Draw the 3d grid, rotated 90 degrees and centered around 0,0 
                // just so we have something in the XY plane
                rlPushMatrix();
                    rlTranslatef(0, 25*50, 0);
                    rlRotatef(90, 1, 0, 0);
                    DrawGrid(100, 50);
                rlPopMatrix();

                // Draw a reference circle
                DrawCircleV(circlePos, circleRadius, YELLOW);
                
            EndMode2D();

            DrawTextEx(font,message,circlePos, 30, 2, WHITE);
        
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    // De-Initialization
    UnloadFont(font);
    //--------------------------------------------------------------------------------------
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------
    return 0;
}