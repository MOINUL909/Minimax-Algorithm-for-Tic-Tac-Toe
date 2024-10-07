#include <stdio.h>
#include <stdbool.h>
#include <string.h>
/*
UserId=Moinul
Password=Moinul909
*/
// Define login credentials
#define USER_ID "Moinul"
#define PASSWORD "Moinul909"

// Game symbols
#define PLAYER 'X'
#define AI 'O'
#define EMPTY '_'

// Function prototypes
bool login();
void printBoard(char board[3][3]);
bool isMovesLeft(char board[3][3]);
int evaluate(char board[3][3]);
int minimax(char board[3][3], int depth, bool isMax);
void findBestMove(char board[3][3], int *bestMoveRow, int *bestMoveCol);
void playerMove(char board[3][3]);
void aiMove(char board[3][3]);

// Function for user login
bool login() {
    char enteredUserId[50], enteredPassword[50];

    printf("Enter User ID: ");
    scanf("%s", enteredUserId);

    printf("Enter Password: ");
    scanf("%s", enteredPassword);

    if (strcmp(enteredUserId, USER_ID) == 0 && strcmp(enteredPassword, PASSWORD) == 0) {
        printf("Login successful!\n");
        return true;
    } else {
        printf("Invalid credentials. Please try again.\n");
        return false;
    }
}

// Print the Tic-Tac-Toe board
void printBoard(char board[3][3]) {
    printf("\n");
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            printf("%c ", board[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

// Check if there are any moves left
bool isMovesLeft(char board[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY)
                return true;
        }
    }
    return false;
}

// Evaluate the board to determine if someone has won
int evaluate(char board[3][3]) {
    // Check rows for victory
    for (int row = 0; row < 3; row++) {
        if (board[row][0] == board[row][1] && board[row][1] == board[row][2]) {
            if (board[row][0] == AI)
                return +10;
            else if (board[row][0] == PLAYER)
                return -10;
        }
    }

    // Check columns for victory
    for (int col = 0; col < 3; col++) {
        if (board[0][col] == board[1][col] && board[1][col] == board[2][col]) {
            if (board[0][col] == AI)
                return +10;
            else if (board[0][col] == PLAYER)
                return -10;
        }
    }

    // Check diagonals for victory
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) {
        if (board[0][0] == AI)
            return +10;
        else if (board[0][0] == PLAYER)
            return -10;
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) {
        if (board[0][2] == AI)
            return +10;
        else if (board[0][2] == PLAYER)
            return -10;
    }

    return 0;
}

// Minimax algorithm with recursion and backtracking
int minimax(char board[3][3], int depth, bool isMax) {
    int score = evaluate(board);

    // If AI has won
    if (score == 10)
        return score - depth;  // Prioritize faster wins

    // If player has won
    if (score == -10)
        return score + depth;  // Prioritize slower losses

    // If no moves left and no winner, it's a draw
    if (!isMovesLeft(board))
        return 0;

    // If it's the maximizer's move (AI)
    if (isMax) {
        int best = -1000;

        // Traverse all cells
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Check if cell is empty
                if (board[i][j] == EMPTY) {
                    // Make the move
                    board[i][j] = AI;

                    // Call minimax recursively
                    best = (best > minimax(board, depth + 1, false)) ? best : minimax(board, depth + 1, false);

                    // Undo the move
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
    // If it's the minimizer's move (human)
    else {
        int best = 1000;

        // Traverse all cells
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                // Check if cell is empty
                if (board[i][j] == EMPTY) {
                    // Make the move
                    board[i][j] = PLAYER;

                    // Call minimax recursively
                    best = (best < minimax(board, depth + 1, true)) ? best : minimax(board, depth + 1, true);

                    // Undo the move
                    board[i][j] = EMPTY;
                }
            }
        }
        return best;
    }
}

// Find the best move for AI
void findBestMove(char board[3][3], int *bestMoveRow, int *bestMoveCol) {
    int bestVal = -1000;

    // Traverse all cells, evaluate minimax for each empty cell
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == EMPTY) {
                // Make the move
                board[i][j] = AI;

                // Compute evaluation function for this move
                int moveVal = minimax(board, 0, false);

                // Undo the move
                board[i][j] = EMPTY;

                // If the value of the current move is better than the best value, update bestMove
                if (moveVal > bestVal) {
                    *bestMoveRow = i;
                    *bestMoveCol = j;
                    bestVal = moveVal;
                }
            }
        }
    }
}

// Get the player's move
void playerMove(char board[3][3]) {
    int row, col;
    printf("Enter your move (row and column): ");
    scanf("%d %d", &row, &col);

    // Ensure move is valid
    while (board[row][col] != EMPTY || row < 0 || row > 2 || col < 0 || col > 2) {
        printf("Invalid move! Enter a valid move (row [0-2] and column [0-2]): ");
        scanf("%d %d", &row, &col);
    }

    board[row][col] = PLAYER;
}

// AI makes its move
void aiMove(char board[3][3]) {
    int bestMoveRow = -1;
    int bestMoveCol = -1;
    findBestMove(board, &bestMoveRow, &bestMoveCol);
    board[bestMoveRow][bestMoveCol] = AI;
    printf("AI plays: Row %d, Col %d\n", bestMoveRow, bestMoveCol);
}

int main() {
    // Login system
    if (!login()) {
        return 1;  // Exit if login fails
    }

    // Initialize the game board
    char board[3][3] = {
        { EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY },
        { EMPTY, EMPTY, EMPTY }
    };

    printf("Tic-Tac-Toe Game: You are 'X', AI is 'O'.\n");
    printBoard(board);

    // Game loop
    while (true) {
        // Player's turn
        playerMove(board);
        printBoard(board);

        // Check if player won
        if (evaluate(board) == -10) {
            printf("You win!\n");
            break;
        }

        // Check for draw
        if (!isMovesLeft(board)) {
            printf("It's a draw!\n");
            break;
        }

        // AI's turn
        aiMove(board);
        printBoard(board);

        // Check if AI won
        if (evaluate(board) == 10) {
            printf("AI wins!\n");
            break;
        }

        // Check for draw
        if (!isMovesLeft(board)) {
            printf("It's a draw!\n");
            break;
        }
    }

    return 0;
}
