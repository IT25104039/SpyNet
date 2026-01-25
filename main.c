#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "grid.h"   
#include "player.h" 
#include "game.h"   
#include "computer.h"

int main() {
    srand(time(NULL));
    
    int N, partChoice, subMode;
    int numPlayers = 0;
    int isP2Computer = 0;

    printf("=== SpyNet: The Codebreaker Protocol ===\n");
    printf("Enter grid size (5-15): ");
    if (scanf("%d", &N) != 1 || N < 5 || N > 15) {
        printf("Error: Grid size must be between 5 and 15.\n");
        return 1;
    }

    printf("\n--- SELECT MISSION TYPE ---\n");
    printf("1. Part 1: Single Player\n");
    printf("2. Part 2: Two Players (Human vs Human/CPU)\n");
    printf("3. Part 3: Three Players (All Human)\n");
    printf("> ");
    if (scanf("%d", &partChoice) != 1) return 1;

    if (partChoice == 1) {
        numPlayers = 1;
    } 
    else if (partChoice == 2) {
        numPlayers = 2;
        printf("\n-- Part 2 Mode --\n");
        printf("1. Human vs Human\n");
        printf("2. Human vs Computer\n");
        printf("> ");
        if (scanf("%d", &subMode) != 1) return 1;
        if (subMode == 2) isP2Computer = 1;
    } 
    else if (partChoice == 3) {
        numPlayers = 3;
    } 
    else {
        printf("Invalid selection.\n");
        return 1;
    }

    char** gameGrid = createGrid(N); 
    initGrid(gameGrid, N); 

    Player agents[3];
    
    initPlayer(&agents[0], '@', 0, 0); 
    
    if (numPlayers >= 2) {
        initPlayer(&agents[1], '&', N-1, N-1);
    } else {
        agents[1].isActive = 0;
    }

    if (numPlayers >= 3) {
        initPlayer(&agents[2], '$', 0, N-1);
    } else {
        agents[2].isActive = 0;
    }


    int turn = 0;
    int gameRunning = 1;

    while (gameRunning) {
        Player* current = &agents[turn];
        
        if (!current->isActive) {
            turn = (turn + 1) % 3; 
            
            if (numPlayers == 1 && turn == 1) turn = 0; 
            if (numPlayers == 2 && turn == 2) turn = 0;
            
            continue; 
        }

        displayGrid(gameGrid, N, agents, numPlayers);
        
        printf("\n--- Player %c's Turn ---\n", current->symbol);
        printf("Lives: %d | Intel: %d/3\n", current->lives, current->intel);

        char input = 0;
        int isComputerTurn = (turn == 1 && isP2Computer);

        if (isComputerTurn) {
            printf("Computer is thinking...\n");
            input = computeMove(current, gameGrid, N);
            printf("Computer chose: %c\n", input);
        } 
        else {
            printf("Enter Move (W/A/S/D): ");
            scanf(" %c", &input);
            while ((getchar()) != '\n');
        }

        if (input == 'Q' || input == 'q') {
            printf("Player %c quit the mission.\n", current->symbol);
            current->isActive = 0;
            if (numPlayers == 1) gameRunning = 0;
        } 
        else {
            movePlayer(current, input, gameGrid, N);
            handleInteractions(current, gameGrid);
            logMove("gamelog.txt", *current, input, gameGrid, N);

            int status = checkGameStatus(current, gameGrid);
            if (status == 1) {
                displayGrid(gameGrid, N, agents, numPlayers);
                printf("\n*** PLAYER %c WINS! ***\n", current->symbol);
                gameRunning = 0;
                break;
            } else if (status == -1) {
                printf("\n>> Player %c eliminated!\n", current->symbol);
                current->isActive = 0;
                if (numPlayers == 1) gameRunning = 0;
            }
        }

        if (numPlayers > 1) {
            int activeCount = 0;
            int winnerIndex = -1;
            for (int i = 0; i < numPlayers; i++) {
                if (agents[i].isActive) {
                    activeCount++;
                    winnerIndex = i;
                }
            }

            if (activeCount == 0) {
                printf("\n*** MISSION FAILED. ALL AGENTS LOST. ***\n");
                gameRunning = 0;
            } 
            else if (activeCount == 1) {
                displayGrid(gameGrid, N, agents, numPlayers);
                printf("\n*** PLAYER %c WINS BY SURVIVAL! ***\n", agents[winnerIndex].symbol);
                gameRunning = 0;
            }
        }

        turn = (turn + 1) % numPlayers;
    }

    freeGrid(gameGrid, N);
    return 0;
}