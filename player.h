#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    int current_row, current_col;
    int lives;
    int intel;
    int isActive;
    char symbol;
} Player;


void initPlayer(Player* p, char symbol, int x, int y);


#endif