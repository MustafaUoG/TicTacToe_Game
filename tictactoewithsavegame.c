#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>

#define MAX_SIZE 10

void playerMove(char board[MAX_SIZE][MAX_SIZE], int size, const char* playerName, char symbol) {
    char rowChar;
    int col;

    while (1) {
        // print player prompt 
        printf("%s, Enter your move: ", playerName);

        scanf(" %c%d", &rowChar, &col);
        
        // this allows the player to input a1 and have the input read as A1
        rowChar = toupper(rowChar);
        int row = rowChar - 'A';
        int colIndex = col - 1;

        if (row < 0 || row >= size || colIndex < 0 || colIndex >= size) {
            printf("Invalid input. Try again.\n");
            continue;
        }

        // this just checks if the space that was selected isn't empty, and if it isn't it prints the following
        if (board[row][colIndex] != ' ') {
            printf("That spot is already taken.\n");
            continue;
        }

        board[row][colIndex] = symbol;
        break;
    }
}

// this function sets every cell on the board to a blank space
void initializeBoard(char board[MAX_SIZE][MAX_SIZE], int size) {

    // goes through every row and column and sets each spot to a space
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            board[i][j] = ' ';   // this makes the board empty
        }
    }
}

// prints the entire board with row letters and column numbers
void printBoard(char board[MAX_SIZE][MAX_SIZE], int size) {

    // prints the column numbers at the top
    printf("    ");
    for (int col = 1; col <= size; col++) {
        printf("%d   ", col);
    }
    printf("\n");

    // prints a line under the numbers
    printf("  ");
    for (int k = 0; k < size; k++) printf("----");
    printf("-\n");

    for (int i = 0; i < size; i++) {

        // prints the row letter on the left
        printf("%c | ", 'A' + i);

        // prints all columns in that row
        for (int j = 0; j < size; j++) {
            printf("%c | ", board[i][j]);
        }
        printf("\n");

        // prints the line after each row
        printf("  ");
        for (int k = 0; k < size; k++) printf("----");
        printf("-\n");
    }
}

// this function shows the game mode menu and returns the user's choice
int selectGameMode() {
    int mode;

    while (1) {
        // this prints the menu options for PVP or PVAI
        printf("Please select your game mode:\n");
        printf("1 - Player Versus Player\n");
        printf("2 - Player Versus AI\n");
        printf("Enter choice: ");

        scanf("%d", &mode);

        // checks valid option
        if (mode == 1 || mode == 2) {
            return mode;  // valid selection
        }

        // if invalid selection
        printf("Invalid choice. Please enter 1 or 2.\n\n");
    }
}

// this function shows the board size menu and returns the actual size value
int selectBoardSize() {
    int boardsize;

    while (1) {
        // this prints the available board sizes
        printf("\nPlease select your stage:\n");
        printf("1 - 3x3\n");
        printf("2 - 5x5\n");
        printf("3 - 10x10\n");
        printf("Enter your choice: ");

        scanf("%d", &boardsize);

        // this converts the menu choice into an actual board size
        if (boardsize == 1) return 3;
        if (boardsize == 2) return 5;
        if (boardsize == 3) return 10;

        // invalid selection
        printf("Invalid choice. Please enter 1, 2, or 3.\n\n");
    }
}

// this function checks if the given input has won the game
int checkWin(char board[MAX_SIZE][MAX_SIZE], int size, char symbol) {

    // check every row
    for (int i = 0; i < size; i++) {
        int rowWin = 1;
        for (int j = 0; j < size; j++) {
            if (board[i][j] != symbol) {
                rowWin = 0;
                break;
            }
        }
        if (rowWin) return 1;
    }

    // check every column
    for (int j = 0; j < size; j++) {
        int colWin = 1;
        for (int i = 0; i < size; i++) {
            if (board[i][j] != symbol) {
                colWin = 0;
                break;
            }
        }
        if (colWin) return 1;
    }

    // check diagonal (top-left to bottom-right)
    int diag1Win = 1;
    for (int i = 0; i < size; i++) {
        if (board[i][i] != symbol) {
            diag1Win = 0;
            break;
        }
    }
    if (diag1Win) return 1;

    // check anti-diagonal (top-right to bottom-left)
    int diag2Win = 1;
    for (int i = 0; i < size; i++) {
        if (board[i][size - 1 - i] != symbol) {
            diag2Win = 0;
            break;
        }
    }
    if (diag2Win) return 1;

    // if no win was found
    return 0;
}

// this function checks if the board has no empty spaces left
int isBoardFull(char board[MAX_SIZE][MAX_SIZE], int size) {

    // goes through every row and column looking for at least one space
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (board[i][j] == ' ') {
                return 0; // not full
            }
        }
    }

    return 1; // board is full
}

/* SMART AI: this tries to win in one move, then tries to block the player.
   If nothing is found, it falls back on a random move. */
void aiMove(char board[MAX_SIZE][MAX_SIZE], int size, char symbol) {
    int row, col;

    // try to win first
    for (row = 0; row < size; row++) {
        for (col = 0; col < size; col++) {
            if (board[row][col] == ' ') {
                board[row][col] = symbol;
                if (checkWin(board, size, symbol)) {
                    return; // AI found a winning move
                }
                board[row][col] = ' ';
            }
        }
    }

    // try to block the player's win
    for (row = 0; row < size; row++) {
        for (col = 0; col < size; col++) {
            if (board[row][col] == ' ') {
                board[row][col] = 'X'; // pretend player moves here
                if (checkWin(board, size, 'X')) {
                    board[row][col] = symbol; // AI blocks
                    return;
                }
                board[row][col] = ' ';
            }
        }
    }

    // fallback: random move
    while (1) {
        row = rand() % size;
        col = rand() % size;

        if (board[row][col] == ' ') {
            board[row][col] = symbol;
            return;
        }
    }
}

// this function saves the current game board to a text file
int saveGame(const char *filename, char board[MAX_SIZE][MAX_SIZE], int size, int mode) {
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error: could not open file '%s' for writing.\n", filename);
        return 0; // failure
    }

    // first line: board size and game mode
    fprintf(fp, "%d %d\n", size, mode);

    // write the board contents, one row per line
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            fputc(board[i][j], fp);
        }
        fputc('\n', fp);
    }

    fclose(fp);
    printf("Game saved successfully to '%s'.\n", filename);
    return 1; // success
}

int main(void) {
   
    // this gives randomness for the AI
    srand(time(NULL));

    int mode = selectGameMode();
    int size = selectBoardSize();

    // this creates the board with the chosen size
    char board[MAX_SIZE][MAX_SIZE];
    initializeBoard(board, size);

    // this prints the empty board at the start of the game
    printBoard(board, size);

    if (mode == 1) {
        while (1) {
            // player 1 turn
            playerMove(board, size, "Player 1", 'X');
            printBoard(board, size);

            // if player 1 made a winning move, end the game
            if (checkWin(board, size, 'X')) {
                printf("Player 1 wins!!!\n");
                break;
            }

            // quick draw check: if board is full and no winner, it's a draw
            {
                int full = 1;
                for (int i = 0; i < size && full; i++)
                    for (int j = 0; j < size; j++)
                        if (board[i][j] == ' ') { full = 0; break; }
                if (full) {
                    printf("It's a draw!!\n");
                    break;
                }
            }

            // player 2 turn
            playerMove(board, size, "Player 2", 'O');
            printBoard(board, size);

            // if player 2 made a winning move, end the game
            if (checkWin(board, size, 'O')) {
                printf("Player 2 wins!!\n");
                break;
            }

            // draw check again after player 2's move
            {
                int full = 1;
                for (int i = 0; i < size && full; i++)
                    for (int j = 0; j < size; j++)
                        if (board[i][j] == ' ') { full = 0; break; }
                if (full) {
                    printf("It's a draw!!\n");
                    break;
                }
            }
        } // end game loop
    } // end PvP 

    // versus AI Mode
    if (mode == 2) {

        while (1) {

            // player turn
            playerMove(board, size, "Player", 'X');
            printBoard(board, size);

            // check if player won
            if (checkWin(board, size, 'X')) {
                printf("You win!\n");
                break;
            }

            // check if board is full
            if (isBoardFull(board, size)) {
                printf("It's a draw!\n");
                break;
            }

            // AI move
            aiMove(board, size, 'O');
            printf("AI played:\n");
            printBoard(board, size);

            // check if AI won
            if (checkWin(board, size, 'O')) {
                printf("The AI wins!!\n");
                break;
            }

            // check draw again
            if (isBoardFull(board, size)) {
                printf("It's a draw!\n");
                break;
            }
        }
    }

    // after the game ends (for either mode), ask if user wants to save the final board
    char savegameChoice;
    printf("Do you want to save this gamefile? (y/n): ");
    scanf(" %c", &savegameChoice);

    if (savegameChoice == 'y' || savegameChoice == 'Y') {
        char filename[100];
        printf("Enter file name (for example: save.txt): ");
        scanf("%99s", filename);

        saveGame(filename, board, size, mode);
    }

    return 0;
}