#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
    int currentRow;
    int currentCol;
    int lives;
    int intel;
    int isActive;
    char symbol;
} Player;


void initPlayer(Player* p, char symbol, int x, int y);
int checkValidMove(char** grid, int r, int c, int n);
int movePlayer(Player* p, char input, char** grid, int n);


#endif