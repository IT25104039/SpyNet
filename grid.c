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
            
            
            int p1Safe = (r == 0 && c == 0) || 
                         (r == 0 && c == 1) || 
                         (r == 1 && c == 0);   

            int p2Safe = (r == n-1 && c == n-1) || 
                         (r == n-1 && c == n-2) || 
                         (r == n-2 && c == n-1);

            int p3Safe = (r == 0 && c == n - 1) ||
                         (r == 0 && c == n - 2) ||
                         (r == 1 && c == n - 1);

            if (grid[r][c] == '.' && !p1Safe && !p2Safe && !p3Safe) {
                grid[r][c] = items[k];
                placed++;
            }
        }
    }
    
}

void displayGrid(char** grid, int n, Player* agents, int numAgents) {
    printf("\n");

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("+---");

        printf("+\n");

        for (int j = 0; j < n; j++) {
            printf("| ");
            
            int drawn = 0;
            for (int k = 0; k < numAgents; k++) {
                if (agents[k].isActive && agents[k].currentRow == i && agents[k].currentCol == j) {
                    printf("%c ", agents[k].symbol);
                    drawn = 1;
                    break;
                }
            }

            if (!drawn) {
                printf("%c ", grid[i][j]);
            }
        }
        printf("|\n");
    }

    for (int i = 0; i < n; i++) printf("+---");
    printf("+\n");
}

void freeGrid(char** grid, int n) {
    for (int i = 0; i < n; i++) {
        free(grid[i]);
    }
    free(grid);
}