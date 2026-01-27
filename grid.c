//Including header files
#include <stdio.h>
#include <stdlib.h>
#include "grid.h"

//function to allocate memory for the grid
char** createGrid(int n) {
    char** grid = (char**)malloc(n * sizeof(char*)); //Creating the "rows" of the grid
    if (grid == NULL) {
        exit(1);
    }

    for (int i = 0; i < n; i++) { //Creating the "columns" of the grid
        grid[i] = (char*)malloc(n * sizeof(char));
        if (grid[i] == NULL) {
            exit(1);
        }
    }
    return grid; //Returning the pointer of the grid
}

//Initializing the grid by placing the symbols in it
void initGrid(char** grid, int n) {

    //Placeholders (.)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            grid[i][j] = '.';
        }
    }
    //Parallel arrays for the specific symbols and their counts
    int counts[4] = {3, 2, 1, n}; 
    char items[4] = {'I', 'L', 'X', '#'};

    //Placing the items
    for (int k = 0; k < 4; k++) {
        int placed = 0;
        while (placed < counts[k]) {
            int r = rand() % n;
            int c = rand() % n;
            
           //Creating safe zones for all the players so no items spawn immediately next to them (used to prevent walls from spawning in such a way that the players cannot move) 
            int p1Safe = (r == 0 && c == 0) || 
                         (r == 0 && c == 1) || 
                         (r == 1 && c == 0);   

            int p2Safe = (r == n-1 && c == n-1) || 
                         (r == n-1 && c == n-2) || 
                         (r == n-2 && c == n-1);

            int p3Safe = (r == 0 && c == n - 1) ||
                         (r == 0 && c == n - 2) ||
                         (r == 1 && c == n - 1);

            //Placing the item if the spot is safe
            if (grid[r][c] == '.' && !p1Safe && !p2Safe && !p3Safe) {
                grid[r][c] = items[k];
                placed++;
            }
        }
    }
    
}

//Function to display the grid to the user
void displayGrid(char** grid, int n, Player* agents, int numAgents) {
    printf("\n");

    //Printing the horizontal bars
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) printf("+---");

        printf("+\n");

        for (int j = 0; j < n; j++) {
            printf("| ");
            
            //Printing the players current positions on the grid
            int drawn = 0;
            for (int k = 0; k < numAgents; k++) {
                if (agents[k].isActive && agents[k].currentRow == i && agents[k].currentCol == j) {
                    printf("%c ", agents[k].symbol);
                    drawn = 1;
                    break;
                }
            }

            //If not already printed, print the character in the grid
            if (!drawn) {
                printf("%c ", grid[i][j]);
            }
        }
        printf("|\n");
    }

    for (int i = 0; i < n; i++) printf("+---");
    printf("+\n");
}

//Fuction to free the memory allocated for the grid
void freeGrid(char** grid, int n) {
    for (int i = 0; i < n; i++) {
        free(grid[i]);
    }
    free(grid);
}