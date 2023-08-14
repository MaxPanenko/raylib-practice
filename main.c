#include <raylib.h>

#define ROWS 3
#define COLS 3
#define CELL_SIZE 100

bool checkIfWin(int board[][COLS], int numROWS, int numCOLS, int player)
{
    // Check rows, columns, and diagonals for a win
    for (int i = 0; i < numROWS; i++) {
        if (board[i][0] == player && board[i][1] == player && board[i][2] == player) 
        {
            return true;
        }
    }

    for (int j = 0; j < numCOLS; j++) {
        if (board[0][j] == player && board[1][j] == player && board[2][j] == player) 
        {
            return true;
        }
    }

    if (board[0][0] == player && board[1][1] == player && board[2][2] == player) 
    {
        return true;
    }

    if (board[0][2] == player && board[1][1] == player && board[2][0] == player) 
    {
        return true;
    }

    return false;
}

int main() {
	SetTargetFPS(60);
    InitWindow(COLS * CELL_SIZE, ROWS * CELL_SIZE, "Tic-Tac-Toe");

    int board[ROWS][COLS] = 
    {{0, 0, 0},
    {0, 0, 0},
    {0, 0, 0}};

    int currentPlayer = 1; // Player 'X'
    bool win = false;

    while (!WindowShouldClose() && !win) 
    {
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) 
        {
            int mouseX = GetMouseX();
            int mouseY = GetMouseY();
            int clickedRow = mouseY / CELL_SIZE;
            int clickedCol = mouseX / CELL_SIZE;

            if (board[clickedRow][clickedCol] == 0)  // Check if cell is empty
            { 
                board[clickedRow][clickedCol] = currentPlayer;

                // Check for win condition
                if (checkIfWin(board, ROWS, COLS, currentPlayer)) 
                {
                    win = true;
                }

                // Switch players
                currentPlayer = (currentPlayer == 1) ? 2 : 1;
            }
        }

        BeginDrawing();
        

        // Draw the game board
        for (int row = 0; row < ROWS; row++) 
        {
            for (int col = 0; col < COLS; col++) 
            {
                DrawRectangle(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE, WHITE);

                // Draw X or O
                if (board[row][col] == 1) 
                {
                    DrawText("x", col * CELL_SIZE + CELL_SIZE / 4, row * CELL_SIZE + CELL_SIZE / 48, CELL_SIZE, RED);
                } 
                else if (board[row][col] == 2) 
                {
                    DrawText("o", col * CELL_SIZE + CELL_SIZE / 4, row * CELL_SIZE + CELL_SIZE / 48, CELL_SIZE, BLACK);
                }

                // Draw cell borders
                DrawRectangleLines(col * CELL_SIZE, row * CELL_SIZE, CELL_SIZE, CELL_SIZE, BLACK);
            }
        }

        EndDrawing();
        ClearBackground(RAYWHITE);
    }


    if(win == true)
    {
		while (!WindowShouldClose())
		    {
		        BeginDrawing();
		        ClearBackground(RAYWHITE);

		        DrawText("Player has won! Press ESC to exit.", 3, GetScreenHeight() / 2, 18, BLACK);

		        EndDrawing();
		        
		        if (IsKeyPressed(KEY_ESCAPE)) 
		        {
		            break; // Exit when ESC key is pressed
		        }
		    }
    }
    else
    {
	    while (!WindowShouldClose())
	    {
	        BeginDrawing();
	        ClearBackground(RAYWHITE);

	        DrawText("DRAW", GetScreenWidth() / 2 - 25, (GetScreenHeight() / 2) - 5, 20, BLACK);

	        EndDrawing();
	        
	        if (IsKeyPressed(KEY_ESCAPE)) 
	        {
	            break;
	        }
	    }
    }

    CloseWindow();
    return 0;

}