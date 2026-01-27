//Including header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "grid.h"   
#include "player.h" 
#include "game.h"   
#include "computer.h"

int main() {
    //Generating a seed for the radnom number function
    srand(time(NULL));
    
    //Initializing and declaring variables needed for the menu
    int N, partChoice, subMode, humanCount;
    int numPlayers = 0;
    
    //Array to keep track of how many players are computers
    int isComputer[3] = {0, 0, 0}; 

    //Asking the user for the grid size
    printf("=== SpyNet: The Codebreaker Protocol ===\n");
    printf("Enter grid size (5-15): ");
    if (scanf("%d", &N) != 1 || N < 5 || N > 15) {
        printf("Error: Grid size must be between 5 and 15.\n");
        return 1;
    }

    //Asking the user for the gamemmode
    printf("\n--- SELECT GAMEMODE ---\n");
    printf("1. Single Player\n");
    printf("2. Two Players\n");
    printf("3. Three Players\n");
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
        
        if (subMode == 2) {
            isComputer[1] = 1;
        }
    } 
    else if (partChoice == 3) {
        numPlayers = 3;
        printf("\n-- Part 3 Mode --\n");
        printf("Enter number of HUMAN players (1-3):\n"); //Asking the user for the number of human players
        printf("(Remaining slots will be filled by Computers)\n> ");
        if (scanf("%d", &humanCount) != 1 || humanCount < 1 || humanCount > 3) {
            printf("Error: Must be 1-3 humans.\n"); //validation
            return 1;
        }

        //Setting up the number of computer players
        if (humanCount == 1) {
            isComputer[1] = 1;
            isComputer[2] = 1;
        } else if (humanCount == 2) {
            isComputer[2] = 1;
        }
    } 
    else {
        printf("Invalid selection.\n");
        return 1;
    }

    //Initializing the grid
    char** gameGrid = createGrid(N); 
    initGrid(gameGrid, N); 

    Player agents[3];
    
   //Initializing the agents 
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

    //Main game loop
    while (gameRunning) {
        Player* current = &agents[turn];
        
        // Skip inactive players
        if (!current->isActive) {
            turn = (turn + 1) % 3; 
            if (numPlayers == 1 && turn == 1) turn = 0; 
            if (numPlayers == 2 && turn == 2) turn = 0;
            continue; 
        }
        
        //Displaying the grid and the menu
        displayGrid(gameGrid, N, agents, numPlayers);
        
        printf("\n--- Player %c's Turn ---\n", current->symbol);
        printf("Lives: %d | Intel: %d/3\n", current->lives, current->intel);

        char input = 0;

        // Checking if the current player a Computer
        if (isComputer[turn]) {
            printf("Computer (%c) is thinking...\n", current->symbol);
            input = computeMove(current, gameGrid, N);
            printf("Computer chose: %c\n", input);
        } 
        else {
            // Human Turn
            printf("Enter Move (W/A/S/D): ");
            scanf(" %c", &input);
            while ((getchar()) != '\n');
        }

        //Quitting if the input is q
        if (input == 'Q' || input == 'q') {
            printf("Player %c quit the game.\n", current->symbol);
            current->isActive = 0;
            if (numPlayers == 1) gameRunning = 0;
        } 
        else {
            //Moving the player and logging the move in the file
            movePlayer(current, input, gameGrid, N);
            handleInteractions(current, gameGrid);
            logMove("gamelog.txt", *current, input, gameGrid, N);

            //Checking if the current player has won
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

        //Checking how many players are still active
        if (numPlayers > 1) {
            int activeCount = 0;
            int winnerIndex = -1;
            for (int i = 0; i < numPlayers; i++) {
                if (agents[i].isActive) {
                    activeCount++;
                    winnerIndex = i;
                }
            }
            //If no players are active, the game ends
            if (activeCount == 0) {
                printf("\n*** MISSION FAILED. ALL AGENTS LOST. ***\n");
                gameRunning = 0;
            } 
            //If only one player is active, that player wins the game
            else if (activeCount == 1) {
                displayGrid(gameGrid, N, agents, numPlayers);
                printf("\n*** PLAYER %c WINS BY SURVIVAL! ***\n", agents[winnerIndex].symbol);
                gameRunning = 0;
            }
        }

        turn = (turn + 1) % numPlayers;
    }
    //Freeing the memory allocated for the grid after the game ends
    freeGrid(gameGrid, N);
    return 0;
}