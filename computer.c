//Including the header files
#include <stdlib.h>
#include "computer.h"
#include "player.h"

//Function to make the computer move
char computeMove(Player* p, char** grid, int n) {
    //Moveset
    char moves[4] = {'W', 'A', 'S', 'D'};

    //Tries 10 times to come up with a valid move
    for (int i = 0; i < 10; i++) {
        //Picking a random move
        int r = rand() % 4;
        char attempt = moves[r];
        
        int testX = p->currentRow;
        int testY = p->currentCol;

        //Changing position based on the move 
        switch (attempt)
        {
        case 'W':
            testX--;
            break;
        case 'S':
            testX++;
            break;
        case 'A':
            testY--;
            break;
        case 'D':
            testY++;
            break;
        }

        //Checking if the move is valid
        if (checkValidMove(grid, testX, testY, n)) {
            return attempt; 
        }
    }

    //If it fails to come up with a move after 10 times, returns a random move
    return moves[rand() % 4];
}