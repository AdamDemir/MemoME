// Mohamad.h Ibrahim 2643344
#include <stdio.h>
#include <time.h>
#include "stdlib.h"

int Boardsize();

int initializeBoard(char **Board, int n);

int getCoordinated(int *row1, int *column1, int *row2, int *column2, int n, char **Board);

int checkCharacters(int row1, int column1, int row2, int column2, int n, char **Board, char **Array);

void displayBoard(char **Array, int n);

int main() {
    int row1, row2, column1, column2, n, Aplayerpoints = 0, Bplayerpoints = 0, allDoorsopened = 0;
    char **Board, **DArray, answer = 'Y';
    srand(time(NULL));
    do {
        printf("Welcome to MemoMe\n");
        // Create the necessarily Board size
        n = Boardsize();
        Board = (char **) malloc(sizeof(char *) * n);
        for (int i = 0; i < n; ++i) {
            Board[i] = (char *) malloc(sizeof(char) * n);
        } // populate it
        initializeBoard(Board, n);
        DArray = (char **) malloc(sizeof(char *) * n);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                DArray[i] = (char *) malloc(sizeof(char) * n);
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                DArray[i][j] = 64;
            }
        }
        do {
            int PlayerATurn = 1;
            int PlayerBTurn = 1;
            while (PlayerATurn) {
                printf("\n\n--Player 1 Turn:--\n\n");
                displayBoard(DArray, n);
                while (!getCoordinated(&row1, &column1, &row2, &column2, n, Board)) { ;
                }
                if(checkCharacters(row1, column1, row2, column2, n, Board, DArray)){
                    displayBoard(DArray, n);
                    Aplayerpoints = Aplayerpoints +2;
                    printf("\n");
                    printf("Lucky you! Your score: 2, total score: %d",Aplayerpoints);
                } else {
                    Aplayerpoints = Aplayerpoints - 1;
                    printf("\n");
                    printf("Unlucky! Your score: -1, total score: %d",Aplayerpoints);
                }
                // finalize the player A turn
                PlayerATurn = 0;
            }
            while (PlayerBTurn) {
                printf("\n\n--Player 2 Turn:--\n\n");
                displayBoard(DArray, n);
                while (!getCoordinated(&row1, &column1, &row2, &column2, n, Board)) { ;
                }
                if(checkCharacters(row1, column1, row2, column2, n, Board, DArray)){
                    displayBoard(DArray, n);
                    Bplayerpoints = Bplayerpoints +2;
                    printf("\n");
                    printf("Lucky you! Your score: 2, total score: %d",Bplayerpoints);
                } else {
                    Bplayerpoints = Bplayerpoints - 1;
                    printf("\n");
                    printf("Unlucky! Your score: -1, total score: %d",Bplayerpoints);
                }
                // finalize the player B turn
                PlayerBTurn = 0;
            }
            // if all doors of the game is opened AKA not @ the all door_opened would be n*n
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    if (DArray[i][j] != 64) {
                        allDoorsopened++;
                    }
                }
            }
        } while (allDoorsopened < n * n);
        printf("\n\nWould you like to play again (Y/N)?\n\n ");
        answer = getchar();
    } while (answer == 'Y');

    return 0;
}

int Boardsize() {
    int n = 0;
    do {
        printf("please specify the Board size (2-32):");
        scanf("%d", &n);
        if (n < 2 || n > 32) {
            printf("Board size can only be between 2-32!\n");
        } else if (n % 2 != 0) {
            printf("Board size can only be a multiple of two!\n");
        }
    } while (n < 2 || n > 32 || n % 2 != 0);
    printf("A board is created for you with the size of %d x %d\n", n, n);
    return n;
}

int initializeBoard(char **Board, int n) {
    int uses_left[n];
    for (int i = 0; i < n; ++i) {
        uses_left[i] = n;
    }
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            int c = 1;
            int Ascii = 0;
            int maxRand = 32 + n;
            while (c) {

                Ascii = 33 + rand() % (maxRand - 32);
                if (uses_left[Ascii - 33] != 0) {
                    uses_left[(Ascii - 33)] = uses_left[(Ascii - 33)] - 1;
                    c = 0;
                }
            }
            Board[i][j] = (char) Ascii;

        }
    }
    return 1;
}

int getCoordinated(int *row1, int *column1, int *row2, int *column2, int n, char **Board) {
    int srow1 = 0, srow2 = 0, scolumn1 = 0, scolumn2 = 0;
    printf("Enter the coordinates of doors to open:");
    scanf(" ( %d ,%d ) ( %d ,%d )", &srow1, &scolumn1, &srow2, &scolumn2);
    printf("\n");
    if (srow1 < 1 || srow1 > n || scolumn1 < 1 || scolumn1 > n || srow2 < 1 || srow2 > n || scolumn2 < 1 ||
        scolumn2 > n) {
        printf("Wrong coordinates\n");
        return 0;
    } else if (srow1 == srow2 && scolumn1 == scolumn2) {
        printf("Sorry, two door coordinates are same!\n");\
        return 0;
    } else if (Board[(srow1 - 1)][(scolumn1 - 1)] == 0 || Board[(srow2 - 1)][(scolumn2 - 1)] == 0) {
        if (Board[(srow1 - 1)][(scolumn1 - 1)] == 0) {
            printf("(%d,%d) is already opened\n", srow1, scolumn1);
        }
        if (Board[(srow2 - 1)][(scolumn2 - 1)] == 0) {
            printf("(%d,%d) is already opened\n", srow2, scolumn2);
        }
        return 0;
    } else {
        *row1 = srow1;
        *column1 = scolumn1;
        *row2 = srow2;
        *column2 = scolumn2;
        return 1;
    }

}

int checkCharacters(int row1, int column1, int row2, int column2, int n, char **Board, char **DArray) {
    if (Board[(row1 - 1 )][(column1 - 1 )] == Board[(row2 - 1 )][(column2 - 1 )]) {
        DArray[(row1 - 1 )][(column1 - 1 )] = Board[(row1 - 1 )][(column1 - 1 )];
        DArray[(row2 - 1 )][(column2 - 1 )] = Board[(row2 - 1 )][(column2 - 1 )];
        Board[(row1 - 1 )][(column1 - 1 )] = 0;
        Board[(row2 - 1 )][(column2 - 1 )] = 0;
        return 1;
    } else {
        DArray[(row1 - 1 )][(column1 - 1 )] = Board[(row1 - 1 )][(column1 - 1 )];
        DArray[(row2 - 1 )][(column2 - 1 )] = Board[(row2 - 1 )][(column2 - 1 )];
        displayBoard(DArray, n);
        DArray[(row1 - 1 )][(column1 - 1 )] = 64;
        DArray[(row2 - 1 )][(column2 - 1 )] = 64;
        return 0;
    }
}

void displayBoard(char **Array, int n) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%c ", Array[i][j]);
        }
        printf("\n");
    }
}