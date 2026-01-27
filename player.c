//Including the header files
#include <stdio.h>
#include <ctype.h>
#include "player.h"

//Function to Initialize the player struct with values
void initPlayer(Player* p, char symbol, int startX, int startY) {
    p->currentRow = startX;
    p->currentCol = startY;
    p->lives = 3;      
    p->intel = 0;       
    p->isActive = 1;    
    p->symbol = symbol; 
}

//Function to check if a move is valid
int checkValidMove(char** grid, int r, int c, int n) {

    //Checking if the row and column are out of bounds
    if (r < 0 || r >= n || c < 0 || c >= n) {
        return 0;
    }
    //Checking for walls
    if (grid[r][c] == '#') {
        return 0;
    }

    return 1;
}

//Function to move the palyer
int movePlayer(Player* p, char input, char** grid, int n) {

    if (!p->isActive) return 0;

    int newRow = p->currentRow;
    int newCol = p->currentCol;
    int validInput = 1; 

    char cmd = toupper(input);

    //Changing the new row and column depending on the user input
    switch (cmd) {
        case 'W': 
            newRow--; 
            break;
        case 'S': 
            newRow++;
            break;
        case 'A':
            newCol--;
            break;
        case 'D':
            newCol++;
            break;
        default: 
            validInput = 0;
            break;
    }
    
    //Checking for invalid inputs
    if (!validInput) {
        
        printf(">> Invalid direction. life lost.\n");
        p->lives--;

    } else if (checkValidMove(grid, newRow, newCol, n)) {

        p->currentRow = newRow;
        p->currentCol = newCol;

    } else {

        printf(">> Obstacle detected. Life lost.\n");
        p->lives--;
    }

    if (p->lives <= 0) {
        p->isActive = 0;
    }

    return 1;
}
