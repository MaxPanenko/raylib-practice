#include "raylib.h"

//------------------------------------------------------------------------------------
int main(void)
{
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "basic window");

    SetTargetFPS(60);             
    //--------------------------------------------------------------------------------------


    int moveRectangle_x = 0;
    int moveRectangle_y = 0;

    while (!WindowShouldClose())    
    {

        moveRectangle_x++;
        moveRectangle_y++;

        BeginDrawing();
        {

            ClearBackground(RAYWHITE);
            DrawCircle(screenWidth/2,screenHeight/2,100,RED);
		}
        EndDrawing();
        //----------------------------------------------------------------------------------
    }

    //--------------------------------------------------------------------------------------
    CloseWindow();
    return 0;
}