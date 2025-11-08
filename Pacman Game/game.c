// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "game.h"

extern char * map, * dot_map;
extern int height;
extern int width;

int check_win(void) {

    for(int i = 0; i < (width * height); i++) {
        if(dot_map[i] == DOT)
            return KEEP_GOING;

    }
    return YOU_WIN;

}

int check_loss(int player_y, int player_x, int ghosts_y[NUM_GHOSTS], int ghosts_x[NUM_GHOSTS]) {
    for (int i = 0; i < NUM_GHOSTS; i++) {
        if (player_y == ghosts_y[i] && player_x == ghosts_x[i]) {
            return YOU_LOSE;
        }
    }
    return KEEP_GOING;


}
