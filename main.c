
#include "raylib.h"

int checkWinner(int board[3][3])
{
    int i;

    // Check rows and columns
    for (i = 0; i < 3; i++)
    {
        if (board[i][0] != 0 &&
            board[i][0] == board[i][1] &&
            board[i][1] == board[i][2])
            return board[i][0];

        if (board[0][i] != 0 &&
            board[0][i] == board[1][i] &&
            board[1][i] == board[2][i])
            return board[0][i];
    }

    // Check diagonals
    if (board[0][0] != 0 &&
        board[0][0] == board[1][1] &&
        board[1][1] == board[2][2])
        return board[0][0];

    if (board[0][2] != 0 &&
        board[0][2] == board[1][1] &&
        board[1][1] == board[2][0])
        return board[0][2];

    return 0;
}

int main()
{
    InitWindow(850, 650, "Tic Tac Toe");
    SetTargetFPS(60);

    int board[3][3] = {0};

    int currentPlayer = 1;
    int winner = 0;
    int gameOver = 0;

    int xScore = 0;
    int oScore = 0;
    int draws = 0;

    int boardX = 50;
    int boardY = 130;
    int cellSize = 150;

    while (!WindowShouldClose())
    {
        // Restart game
        if (IsKeyPressed(KEY_R))
        {
            for (int r = 0; r < 3; r++)
            {
                for (int c = 0; c < 3; c++)
                {
                    board[r][c] = 0;
                }
            }

            currentPlayer = 1;
            winner = 0;
            gameOver = 0;
        }

        // Handle mouse clicks
        if (!gameOver && IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Vector2 mouse = GetMousePosition();

            if (mouse.x >= boardX &&
                mouse.x < boardX + 450 &&
                mouse.y >= boardY &&
                mouse.y < boardY + 450)
            {
                int col = (mouse.x - boardX) / cellSize;
                int row = (mouse.y - boardY) / cellSize;

                if (board[row][col] == 0)
                {
                    board[row][col] = currentPlayer;

                    winner = checkWinner(board);

                    if (winner != 0)
                    {
                        gameOver = 1;

                        if (winner == 1)
                            xScore++;
                        else
                            oScore++;
                    }
                    else
                    {
                        int full = 1;

                        for (int r = 0; r < 3; r++)
                        {
                            for (int c = 0; c < 3; c++)
                            {
                                if (board[r][c] == 0)
                                    full = 0;
                            }
                        }

                        if (full)
                        {
                            gameOver = 1;
                            draws++;
                        }
                        else
                        {
                            if (currentPlayer == 1)
                                currentPlayer = 2;
                            else
                                currentPlayer = 1;
                        }
                    }
                }
            }
        }

        // Drawing
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("TIC TAC TOE", 50, 40, 35, DARKBLUE);

        // Draw grid
        for (int i = 1; i < 3; i++)
        {
            DrawLine(boardX + i * cellSize, boardY,
                     boardX + i * cellSize, boardY + 450, BLACK);

            DrawLine(boardX, boardY + i * cellSize,
                     boardX + 450, boardY + i * cellSize, BLACK);
        }

        // Draw X and O
        for (int r = 0; r < 3; r++)
        {
            for (int c = 0; c < 3; c++)
            {
                int x = boardX + c * cellSize;
                int y = boardY + r * cellSize;

                if (board[r][c] == 1)
                {
                    DrawLine(x + 35, y + 35, x + 115, y + 115, BLUE);
                    DrawLine(x + 115, y + 35, x + 35, y + 115, BLUE);
                }
                else if (board[r][c] == 2)
                {
                    DrawCircleLines(x + 75, y + 75, 45, RED);
                }
            }
        }

        // Display scores
        DrawText("SCOREBOARD", 570, 150, 25, DARKBLUE);

        DrawText(TextFormat("X Wins: %d", xScore), 570, 210, 22, BLUE);
        DrawText(TextFormat("O Wins: %d", oScore), 570, 260, 22, RED);
        DrawText(TextFormat("Draws: %d", draws), 570, 310, 22, BLACK);

        // Display game status
        if (winner == 1)
            DrawText("X WINS!", 570, 400, 25, BLUE);
        else if (winner == 2)
            DrawText("O WINS!", 570, 400, 25, RED);
        else if (gameOver)
            DrawText("IT'S A DRAW!", 570, 400, 25, DARKGRAY);
        else if (currentPlayer == 1)
            DrawText("X'S TURN", 570, 400, 25, BLUE);
        else
            DrawText("O'S TURN", 570, 400, 25, RED);

        DrawText("Press R to restart", 570, 470, 18, DARKGRAY);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}
