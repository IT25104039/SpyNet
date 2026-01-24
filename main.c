#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "grid.h"   
#include "player.h" 
#include "game.h"   
#include "computer.h"

int main() {
    srand(time(NULL));
    
    int N;
    int mode;
    
    printf("=== SpyNet: The Codebreaker Protocol ===\n");
    printf("Enter grid size (5-15): ");
    
    if (scanf("%d", &N) != 1 || N < 5 || N > 15) {
        printf("Error: Grid size must be between 5 and 15.\n");
        return 1;
    }

    printf("\nSelect Game Mode:\n");
    printf("1. Human vs. Human\n");
    printf("2. Human vs. Computer\n");
    printf("> ");
    if (scanf("%d", &mode) != 1 || (mode != 1 && mode != 2)) {
        printf("Error: Invalid mode selection.\n");
        return 1;
    }

    char** gameGrid = createGrid(N); 
    initGrid(gameGrid, N); 

    Player agents[2];
    
    initPlayer(&agents[0], '@', 0, 0); 
    gameGrid[0][0] = '.';

    initPlayer(&agents[1], '&', N-1, N-1);
    gameGrid[N-1][N-1] = '.';

    printf("\nMission Start. Collect 3 Intel (I) and reach Extraction (X).\n");

    int turn = 0;
    int gameRunning = 1;

    while (gameRunning) {
        Player* current = &agents[turn];
        
        if (!current->isActive) {
            turn = !turn;
            continue; 
        }

        displayGrid(gameGrid, N, agents, 2);
        
        printf("\n--- Player %c's Turn ---\n", current->symbol);
        printf("Lives: %d | Intel: %d/3\n", current->lives, current->intel);

        char input = 0;

        if (turn == 0) {
            printf("Move (W/A/S/D) or Q to quit: ");
            scanf(" %c", &input);
            while ((getchar()) != '\n'); 
        } 
        else {
            if (mode == 1) {
                printf("Move (I/J/K/L) or Q to quit: ");
                scanf(" %c", &input);
                while ((getchar()) != '\n'); 

                if (input == 'i' || input == 'I') input = 'w';
                else if (input == 'k' || input == 'K') input = 's';
                else if (input == 'j' || input == 'J') input = 'a';
                else if (input == 'l' || input == 'L') input = 'd';
            } 
            else {
                printf("Computer is thinking...\n");
                input = computeMove(current, gameGrid, N); 
                printf("Computer chose: %c\n", input);
            }
        }

        if (input == 'Q' || input == 'q') {
            printf("Player %c quit the mission.\n", current->symbol);
            current->isActive = 0;
            if (turn == 0) gameRunning = 0;
        } else {
            movePlayer(current, input, gameGrid, N);
            handleInteractions(current, gameGrid);
            logMove("gamelog.txt", *current, input, gameGrid, N);

            int status = checkGameStatus(current, gameGrid);

            if (status == 1) {
                displayGrid(gameGrid, N, agents, 2);
                printf("\n*** PLAYER %c WINS! ***\n", current->symbol);
                gameRunning = 0;
            } 
            else if (status == -1) {
                printf("\n>> Player %c has been eliminated!\n", current->symbol);
                current->isActive = 0; 

                if (turn == 0) {
                    printf("*** MISSION FAILED: You were neutralized. ***\n");
                    gameRunning = 0;
                } else {
                    printf(">> Target Down. Continue the mission, Agent!\n");
                }
            }
        }

        turn = !turn;
    }

    freeGrid(gameGrid, N);
    
    return 0;
}