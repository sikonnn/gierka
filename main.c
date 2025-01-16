#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 5
#define WIN_COUNT 4

void initializeBoard(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            board[i][j] = ' ';
        }
    }
}

void printBoard(char board[SIZE][SIZE]) {
    printf("\n");
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            printf(" %c ", board[i][j]);
            if (j < SIZE - 1) printf("|");
        }
        printf("\n");
        if (i < SIZE - 1) {
            for (int k = 0; k < SIZE; k++) {
                printf("---");
                if (k < SIZE - 1) printf("+");
            }
            printf("\n");
        }
    }
    printf("\n");
}

int checkWin(char board[SIZE][SIZE], char symbol) {
    // Check rows
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j <= SIZE - WIN_COUNT; j++) {
            int count = 0;
            for (int k = 0; k < WIN_COUNT; k++) {
                if (board[i][j + k] == symbol) count++;
            }
            if (count == WIN_COUNT) return 1;
        }
    }

    // Check columns
    for (int i = 0; i <= SIZE - WIN_COUNT; i++) {
        for (int j = 0; j < SIZE; j++) {
            int count = 0;
            for (int k = 0; k < WIN_COUNT; k++) {
                if (board[i + k][j] == symbol) count++;
            }
            if (count == WIN_COUNT) return 1;
        }
    }

    // Check diagonals (top-left to bottom-right)
    for (int i = 0; i <= SIZE - WIN_COUNT; i++) {
        for (int j = 0; j <= SIZE - WIN_COUNT; j++) {
            int count = 0;
            for (int k = 0; k < WIN_COUNT; k++) {
                if (board[i + k][j + k] == symbol) count++;
            }
            if (count == WIN_COUNT) return 1;
        }
    }

    // Check diagonals (top-right to bottom-left)
    for (int i = 0; i <= SIZE - WIN_COUNT; i++) {
        for (int j = WIN_COUNT - 1; j < SIZE; j++) {
            int count = 0;
            for (int k = 0; k < WIN_COUNT; k++) {
                if (board[i + k][j - k] == symbol) count++;
            }
            if (count == WIN_COUNT) return 1;
        }
    }

    return 0;
}

int isBoardFull(char board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') return 0;
        }
    }
    return 1;
}

int canBlockTwoInRow(char board[SIZE][SIZE], char symbol, int *x, int *y) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE - 2; j++) {
            if (board[i][j] == symbol && board[i][j + 1] == symbol && board[i][j + 2] == ' ') {
                *x = i;
                *y = j + 2;
                return 1;
            }
            if (board[i][j] == ' ' && board[i][j + 1] == symbol && board[i][j + 2] == symbol) {
                *x = i;
                *y = j;
                return 1;
            }
        }
    }

    for (int j = 0; j < SIZE; j++) {
        for (int i = 0; i < SIZE - 2; i++) {
            if (board[i][j] == symbol && board[i + 1][j] == symbol && board[i + 2][j] == ' ') {
                *x = i + 2;
                *y = j;
                return 1;
            }
            if (board[i][j] == ' ' && board[i + 1][j] == symbol && board[i + 2][j] == symbol) {
                *x = i;
                *y = j;
                return 1;
            }
        }
    }

    for (int i = 0; i < SIZE - 2; i++) {
        for (int j = 0; j < SIZE - 2; j++) {
            if (board[i][j] == symbol && board[i + 1][j + 1] == symbol && board[i + 2][j + 2] == ' ') {
                *x = i + 2;
                *y = j + 2;
                return 1;
            }
            if (board[i][j] == ' ' && board[i + 1][j + 1] == symbol && board[i + 2][j + 2] == symbol) {
                *x = i;
                *y = j;
                return 1;
            }
        }
    }

    for (int i = 0; i < SIZE - 2; i++) {
        for (int j = 2; j < SIZE; j++) {
            if (board[i][j] == symbol && board[i + 1][j - 1] == symbol && board[i + 2][j - 2] == ' ') {
                *x = i + 2;
                *y = j - 2;
                return 1;
            }
            if (board[i][j] == ' ' && board[i + 1][j - 1] == symbol && board[i + 2][j - 2] == symbol) {
                *x = i;
                *y = j;
                return 1;
            }
        }
    }

    return 0;
}

int canWinNextMove(char board[SIZE][SIZE], char symbol, int *x, int *y) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = symbol;
                if (checkWin(board, symbol)) {
                    *x = i;
                    *y = j;
                    board[i][j] = ' ';
                    return 1;
                }
                board[i][j] = ' ';
            }
        }
    }
    return 0;
}

void computerMove(char board[SIZE][SIZE]) {
    int x, y;

    if (canWinNextMove(board, 'O', &x, &y)) {
        board[x][y] = 'O';
        printf("Computer places 'O' at %d %d\n", x + 1, y + 1);
        return;
    }

    if (canWinNextMove(board, 'X', &x, &y)) {
        board[x][y] = 'O';
        printf("Computer blocks at %d %d\n", x + 1, y + 1);
        return;
    }

    if (canBlockTwoInRow(board, 'X', &x, &y)) {
        board[x][y] = 'O';
        printf("Computer blocks potential line at %d %d\n", x + 1, y + 1);
        return;
    }

    srand(time(NULL));
    while (1) {
        x = rand() % SIZE;
        y = rand() % SIZE;
        if (board[x][y] == ' ') {
            board[x][y] = 'O';
            printf("Computer places 'O' at %d %d\n", x + 1, y + 1);
            break;
        }
    }
}

void playerMove(char board[SIZE][SIZE]) {
    int x, y;
    while (1) {
        printf("Enter your move (row and column): ");
        if (scanf("%d %d", &x, &y) != 2) {
            printf("Invalid input. Please enter two numbers.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        if (x >= 1 && x <= SIZE && y >= 1 && y <= SIZE && board[x - 1][y - 1] == ' ') {
            board[x - 1][y - 1] = 'X';
            break;
        } else {
            printf("Invalid move. Try again.\n");
        }
    }
}

int main() {
    char board[SIZE][SIZE];
    initializeBoard(board);

    printf(Witam w grze kółko i kryżyk!\n");
    printBoard(board);

    while (1) {
        playerMove(board);
        printBoard(board);
        if (checkWin(board, 'X')) {
            printf("Wygrana!!!\n");
            break;
        }
        if (isBoardFull(board)) {
            printf("Remis!\n");
            break;
        }

        computerMove(board);
        printBoard(board);
        if (checkWin(board, 'O')) {
            printf("Przegrałeś ;pp.\n");
            break;
        }
        if (isBoardFull(board)) {
            printf("Remis!\n");
            break;
        }
    }

    return 0;
}
