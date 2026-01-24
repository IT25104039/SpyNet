#include <stdlib.h>
#include "computer.h"
#include "player.h"

char computeMove(Player* p, char** grid, int n) {
    char moves[4] = {'W', 'A', 'S', 'D'};

    for (int i = 0; i < 10; i++) {
        int r = rand() % 4;
        char attempt = moves[r];
        
        int testX = p->currentRow;
        int testY = p->currentCol;
        
        if (attempt == 'W') testX--;
        else if (attempt == 'S') testX++;
        else if (attempt == 'A') testY--;
        else if (attempt == 'D') testY++;

        if (checkValidMove(grid, testX, testY, n)) {
            return attempt; 
        }
    }

    return moves[rand() % 4];
}