// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include "defines.h"
#include "actor.h"

extern char * map, * dot_map;
extern int height;
extern int width;

char sees_player(int player_y, int player_x, int ghost_y, int ghost_x) {

    if (player_y == ghost_y && player_x == ghost_x) {//if the player and ghost coords are the same
        return EATING_PLAYER;
    }

    //check the vertical plane
    if (player_x == ghost_x) {
        if (player_y > ghost_y) {
            //check downward
            for (int y = ghost_y + 1; y <= player_y; y++) {
                if (map[y * width + ghost_x] == WALL)
                    break;
                if (y == player_y) //if the ghost y == player y ghost will go down
                    return DOWN;
            }
        } else {
            //check upward
            for (int y = ghost_y - 1; y >= player_y; y--) {

                if (map[y * width + ghost_x] == WALL)
                    break;
                if (y == player_y) //if the ghost y == player y ghost will go up
                    return UP;
            }
        }
    }
        //check the horizontal plane
    else if (player_y == ghost_y) {
        if (player_x > ghost_x) {
            //check the right pathway
            for (int x = ghost_x + 1; x <= player_x; x++) {
                if (map[ghost_y * width + x] == WALL)
                    break;
                if (x == player_x) //if the ghost x == player x ghost will go right
                    return RIGHT;
            }
        } else {
            //check the left pathway
            for (int x = ghost_x - 1; x >= player_x; x--) {
                if (map[ghost_y * width + x] == WALL)
                    break;
                if (x == player_x) //if the ghost x == player x ghost will go left
                    return LEFT;
            }
        }
    }
    return SEES_NOTHING;
}

int move_player(int* y, int* x, char direction) {

    int new_y = *y;
    int new_x = *x;


    if(direction != RIGHT && direction != LEFT && direction != UP && direction != DOWN) {
        return MOVED_INVALID_DIRECTION;
    }



    if(direction == RIGHT) {
        if ((map[new_y * width + (new_x + 1)]) == WALL || ((new_x + 1 >= width))) { //check if the move takes player into wall or border


            return MOVED_WALL;


        } else
            new_x++;
    }

    if(direction == LEFT) {
        if ((map[new_y * width + (new_x - 1)]) == WALL || new_x - 1 < 0) { //check if the move takes player into wall or border
            return MOVED_WALL;

        } else
            new_x--;
    }

    if(direction == UP) {
        if ((map[(new_y - 1) * width + new_x]) == WALL || new_y - 1 < 0) { //check if the move takes player into wall or border
            return MOVED_WALL;

        } else
            new_y--;

    }

    if(direction == DOWN) {
        if ((map[(new_y + 1) * width + new_x]) == WALL || new_y + 1 >= height) {//check if the move takes player into wall or border
            return MOVED_WALL;

        } else
            new_y++;
    }


    if(map[new_y * width + new_x] == DOT || map[new_y * width + new_x] == EMPTY) { //if the move does not take you into a wall

        map[*y * width + *x] = EMPTY;
        map[new_y * width + new_x] = PLAYER;
        dot_map[new_y * width + new_x] = EMPTY; //update the dot map


        *y = new_y;
        *x = new_x;

        return MOVED_OKAY;
    }

    return MOVED_WALL; //if the move takes you into a wall
}

int move_ghost(int * ghost_y, int * ghost_x, char direction) {

    int new_x = *ghost_x;
    int new_y = *ghost_y;


    //check movement and check if the ghost runs into a wall
    // Check bounds BEFORE accessing map
    if (direction == RIGHT) {
        if ((new_x + 1 >= width) || (map[new_y * width + (new_x + 1)] == WALL)) {
            return MOVED_WALL;
        }
        new_x++;
    }
    else if (direction == LEFT) {
        if ((new_x - 1 < 0) || (map[new_y * width + (new_x - 1)] == WALL)) {
            return MOVED_WALL;
        }
        new_x--;
    }
    else if (direction == UP) {
        if ((new_y - 1 < 0) || (map[(new_y - 1) * width + new_x] == WALL)) {
            return MOVED_WALL;
        }
        new_y--;
    }
    else if (direction == DOWN) {
        if ((new_y + 1 >= height) || (map[(new_y + 1) * width + new_x] == WALL)) {
            return MOVED_WALL;
        }
        new_y++;
    }
    else {
        return MOVED_INVALID_DIRECTION;
    }

    //clear the old ghost position and replace it with what it was covering on the dot_map
    if (dot_map[*ghost_y * width + *ghost_x] == DOT) {
        map[*ghost_y * width + *ghost_x] = DOT;
    } else {
        map[*ghost_y * width + *ghost_x] = EMPTY;
    }

    //update the ghost position on the map
    *ghost_x = new_x;
    *ghost_y = new_y;
    map[new_y * width + new_x] = GHOST;

    return MOVED_OKAY;

}

