#ifndef GRID_H
#define GRID_H

#include "player.h"

char** createGrid(int n);
void initGrid(char** grid, int n);
void displayGrid(char** grid, int n, Player* agents, int numAgents);
void freeGrid(char** grid, int n);


#endif