//Including the header files
#include <stdio.h>
#include "game.h"

//Fuction to handle player interactions with items on the grid 
void handleInteractions(Player* p, char** grid) {

    char cellValue = grid[p->currentRow][p->currentCol];

    //Handling intel collection
    if (cellValue == 'I') {
        p->intel++;
        grid[p->currentRow][p->currentCol] = '.';
        printf("Intel found. Total intel count: %d/3\n", p->intel);
    } 
    //Handling life collection
    else if (cellValue == 'L') {
        p->lives++;
        grid[p->currentRow][p->currentCol] = '.';
        printf("Extra life found. Total Life count: %d/3\n", p->lives);

    }
}

//Function to check if players are active or not 
int checkGameStatus(Player* p, char** grid) {

    //Checking if the player has all the required intel when reaching the extraction point
    if (grid[p->currentRow][p->currentCol] == 'X') {
        if (p->intel >= 3) {
            return 1;
        } else {
            p->isActive = 0;
            return -1;
        }
    }

    //Making the player inactive when the lives reach 0
    if (p->lives <= 0) {
        p->isActive = 0;
        return -1;
    }

    return 0;
}

//Function to log the moves to a text file
void logMove(const char* filename, Player p, char lastMove, char** grid, int n) {
    FILE* fptr = fopen(filename, "a"); 
    if (fptr == NULL) return;

    //Writing the content to the file
    fprintf(fptr, "Action: %c | Pos: (%d,%d) | Lives: %d | Intel: %d/3\n", 
            lastMove, p.currentRow, p.currentCol, p.lives, p.intel);

    //Writing the grid
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (i == p.currentRow && j == p.currentCol) fprintf(fptr, "%c ", p.symbol);
            else fprintf(fptr, "%c ", grid[i][j]);
        }
        fprintf(fptr, "\n");
    }
    fprintf(fptr, "--------------------------\n");
    fclose(fptr);
}

