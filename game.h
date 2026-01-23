#ifndef GAME_H
#define GAME_H

#include "player.h"

void handleInteractions(Player* p, char** grid);
int checkGameStatus(Player* p, char** grid);
void logMove(const char* filename, Player p, char lastMove, char** grid, int n);

#endif