#include <stdio.h>
#include "game.h"

void handleInteractions(Player* p, char** grid) {

    char cellValue = grid[p->currentRow][p->currentCol];

    if (cellValue == 'I') {
        p->intel++;
        grid[p->currentRow][p->currentCol] = '.';
        printf("Intel found. Total intel count: %d/3\n", p->intel);
    } 
    else if (cellValue == 'L') {
        p->lives++;
        grid[p->currentRow][p->currentCol] = '.';
        printf("Extra life found. Total Life count: %d/3\n", p->lives);

    }
}

int checkGameStatus(Player* p, char** grid) {

    if (grid[p->currentRow][p->currentCol] == 'X') {
        if (p->intel >= 3) {
            return 1;
        } else {
            p->isActive = 0;
            return -1;
        }
    }

    if (p->lives <= 0) {
        p->isActive = 0;
        return -1;
    }

    return 0;
}

void logMove(const char* filename, Player p, char lastMove, char** grid, int n) {
    FILE* fptr = fopen(filename, "a"); 
    if (fptr == NULL) return;

    fprintf(fptr, "Action: %c | Pos: (%d,%d) | Lives: %d | Intel: %d/3\n", 
            lastMove, p.currentRow, p.currentCol, p.lives, p.intel);

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

