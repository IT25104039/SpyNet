
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "grid.h"   
#include "player.h" 
#include "game.h"   

int main() {
    srand(time(NULL));
    
    int N;
    char input;

    printf("=== SpyNet: The Codebreaker Protocol ===\n");
    printf("Enter grid size (5-15): ");
    

    if (scanf("%d", &N) != 1 || N < 5 || N > 15) {
        printf("Error: Grid size must be between 5 and 15.\n");
        return 1;
    }


    char** gameGrid = createGrid(N); 
    initGrid(gameGrid, N); 

    Player p1;
    initPlayer(&p1, '@', 0, 0); 
    

    gameGrid[0][0] = '.'; 

    printf("Mission Start. Collect 3 Intel (1) and reach Extraction (X).\n");


    while (p1.isActive) {
        

        displayGrid(gameGrid, N, p1);
        printf("Agent %c | Lives: %d | Intel: %d/3\n", p1.symbol, p1.lives, p1.intel);
        printf("Move (W/A/S/D) or Q to quit: ");

        scanf(" %c", &input); 


        if (input == 'Q' || input == 'q') {
            printf("Mission Aborted by User.\n");
            p1.isActive = 0; 
            logMove("gamelog.txt", p1, input, gameGrid, N);
            break;
        }


        movePlayer(&p1, input, gameGrid, N);
        handleInteractions(&p1, gameGrid);
        logMove("gamelog.txt", p1, input, gameGrid, N); 

        int status = checkGameStatus(&p1, gameGrid);

        if (status == 1) {
            displayGrid(gameGrid, N, p1);
            printf("\n*** MISSION ACCOMPLISHED ***\n");
            printf("Intel secured. Extraction successful.\n");
            break;
        } 
        else if (status == -1) {
            displayGrid(gameGrid, N, p1);
            printf("\n*** MISSION FAILED ***\n");
            
            if (p1.lives <= 0) printf("Agent neutralized (Lives: 0).\n");
            else printf("Extracted without required Intel.\n");
            
            break;
        }
    }

    freeGrid(gameGrid, N);
    
    return 0;
}