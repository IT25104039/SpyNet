#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

char** createGrid(int n) {
    char** grid = (char**)malloc(n * sizeof(char*));
    if (grid == NULL) {
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        grid[i] = (char*)malloc(n * sizeof(char));
        if (grid[i] == NULL) {
            exit(1);
        }
    }
    return grid;
}

void initGrid(char** grid, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = '.';
        }
    }

    int counts[4] = {3, 2, 1, n};
    char items[4] = {'I', 'L', 'X', '#'};

    for (int k = 0; k < 4; k++) {
        int placed = 0;
        while (placed < counts[k]) {
            int r = rand() % n;
            int c = rand() % n;
            
            if (grid[r][c] == '.' && (r != 0 || c != 0)) {
                grid[r][c] = items[k];
                placed++;
            }
        }
    }

	grid[0][1] = '.'; 
    grid[1][0] = '.'; 
    grid[1][1] = '.';
}

void displayGrid(char** grid, int n, Player p) {
    printf("\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("+---");
        }
        printf("+\n");

        for (int j = 0; j < n; j++) {
            printf("| ");
            if (i == p.currentRow && j == p.currentCol) {
                printf("%c ", p.symbol);
            } else {
                printf("%c ", grid[i][j]);
            }
        }
        printf("|\n");
    }

    for (int i = 0; i < n; i++) {
        printf("+---");
    }
    printf("+\n");
}

void freeGrid(char** grid, int n) {
    for (int i = 0; i < n; i++) {
        free(grid[i]);
    }
    free(grid);
}