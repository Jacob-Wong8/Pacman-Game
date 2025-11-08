// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

// don't forget to update your project configuration to select "Emulate terminal in the output console"

// Make sure to include all relevant libraries
#include <stdio.h>
#include <stdlib.h>

// colours.h contains functions to change text colour and read single characters without requiring an enter
#include "colours.h"
// defines.h contains useful definitions to keep your code readable
#include "defines.h"
// map.h, game.h, and ghost.h contain prototypes of functions you must implement
#include "map.h"
#include "game.h"
#include "actor.h"

// These global variables must be used to store map information.
// Almost every function needs these variables, so keeping them as globals helps keep things organized.
// map is a pointer to a dynamically allocated map for displaying to the user
// dot_map is a pointer to a dynamically allocated map for keeping track of what dots are left
char *map = NULL, *dot_map = NULL;
// width and height store the width and height of map, NOT counting outer walls
int width, height;


#define HARDCODED_WIDTH 9
#define HARDCODED_HEIGHT 9
char hardcoded_map[] = {
        GHOST, DOT, DOT, DOT, WALL, DOT, DOT, DOT, EMPTY,
        DOT, WALL, WALL, DOT, WALL, DOT, WALL, WALL, DOT,
        DOT, WALL, DOT, DOT, DOT, DOT, DOT, WALL, DOT,
        DOT, WALL, DOT, WALL, WALL, WALL, DOT, WALL, DOT,
        DOT, DOT, DOT, DOT, PLAYER, DOT, DOT, DOT, DOT,
        DOT, WALL, DOT, WALL, WALL, WALL, DOT, WALL, DOT,
        DOT, WALL, DOT, DOT, DOT, DOT, DOT, WALL, DOT,
        DOT, WALL, WALL, DOT, WALL, DOT, WALL, WALL, DOT,
        EMPTY, DOT, DOT, DOT, WALL, DOT, DOT, DOT, GHOST
};


/**
 * Updates the positions of the ghosts.
 * For a passed ghosts, this function checks if they can see the
 * player and moves them accordingly.  If a ghost can see the player,
 * it must move towards the player.  Otherwise, the ghost will move
 * in a random valid direction (not into a wall).  If the ghost is
 * trapped by walls in all four directions, it should give up and
 * not move.
 *
 * The ghosts_y and ghosts_x arrays are meant to hold NUM_GHOSTS
 * coordinates.  So, index 0 of ghosts_x holds the X coordinate
 * of ghost 0 and index 0 of ghosts_y holds the Y coordinate of
 * ghost 0.
 * @param player_y The Y coordinate of player
 * @param player_x The X coordinate of player
 * @param ghost_y A pointer to the Y coordinates of a ghost
 * @param ghost_x A pointer to the X coordinates of a ghost
 * @return
 */
void update_ghost(int player_y, int player_x, int * ghost_y, int * ghost_x);
void find_player(int *player_y, int *player_x);
void find_ghosts(int ghost_y[], int ghost_x[]);


// define a return code for a memory error
#define ERR_MEMORY 4

/**
 * Main entry point into your program.
 * Make sure that main returns appropriate status codes depending on what
 * happens.  The codes you must use are:
 *   NO_ERROR when no error occurs
 *   ERR_NO_MAP when no map file is found
 *   ERR_NO_PLAYER when no player is found on the map
 *   ERR_NO_GHOSTS when fewer than 2 ghosts are found on the map
 *
 * Make sure that any allocated memory is freed before returning.
 * @return a status code
 */
int main(void) {
    // This ensures that printf writes to the console immediately, instead of buffering.
    // If you remove this, you will not be able to rely on printf to work if your program crashes.
    setbuf(stdout, NULL);

    // set the map to point to the hardcoded map
    // width = HARDCODED_WIDTH;
    // height = HARDCODED_HEIGHT;
    // we don't actually have to use dot_map for lab1
    map = load_map("map.txt", &height, &width);
    // allocate space for the dots
    dot_map = malloc(width * height);

    if (map == NULL) {
        return ERR_NO_MAP;
    }
    if (dot_map == NULL) {
        return ERR_NO_MAP;
    }


    int player_x = 0;
    int player_y = 0;
    find_player(&player_y, &player_x);

    if (map[player_y * width + player_x] != PLAYER) { //if there is no player
        return ERR_NO_PLAYER; //return 1
    }

// check if at least 2 ghosts are present
    int ghosts_y[NUM_GHOSTS];
    int ghosts_x[NUM_GHOSTS];
    find_ghosts(ghosts_y, ghosts_x);
    if (map[ghosts_y[0] * width + ghosts_x[0]] != GHOST ||
        map[ghosts_y[1] * width + ghosts_x[1]] != GHOST) {
        return ERR_NO_GHOSTS;
    }

    // copy dots into dot_map
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            if (map[y * width + x] == DOT) {
                dot_map[y * width + x] = DOT;
            } else {
                dot_map[y * width + x] = EMPTY;
            }
        }
    }

    // input holds the user input
    char input = 0;
    // we need the player position - we can hardcode it for now
    player_x = 0;
    player_y = 0;
    find_player(&player_y, &player_x);

    // we also need the ghosts positions - we can again hardcode them

    find_ghosts(ghosts_y, ghosts_x);

    // loop until we hit the end of input
    while (input != EOF) {



        if(check_loss(player_y, player_x, ghosts_y, ghosts_x) == YOU_LOSE) {
            print_map();
            printf("Sorry, you lose.");
            break;
        }

        if(check_win() == YOU_WIN) {
            print_map();
            printf("Congratulations! You win!");
            break;

        }


        // print the map
        print_map();

        // get a character - blocks until one is input
        input = getch();

        // move the player
        move_player(&player_y, &player_x, input);

        // update the ghosts
        for (int ghost = 0; ghost < NUM_GHOSTS; ghost++) {
            update_ghost(player_y, player_x, &ghosts_y[ghost], &ghosts_x[ghost]);
        }

    } // quit if we hit the end of input

    // free the dot_map
    free(dot_map);

    //free map
    free(map);


    // You must return the correct error code from defines.h from main depending on what happened
    return NO_ERROR;
}


void update_ghost(int player_y, int player_x, int * ghost_y, int * ghost_x) { //generates random direction if it doesnt see player
    // check if the ghost can see the player
    char direction = sees_player(player_y, player_x, *ghost_y, *ghost_x);

    // if the ghost doesn't see the player
    if (direction == SEES_NOTHING) {
        // get a random direction, keeping track of if we already tried it
        char tried_directions[] = {0,0,0,0};
        char direction_map[] = {UP, LEFT, DOWN, RIGHT};
        int move_result;
        do {
            // get a random direction
            int direction_int = rand() % 4;
            // set that we tried the direction
            tried_directions[direction_int] = 1;
            // get the input direction to move
            direction = direction_map[direction_int];
            // try it!
            move_result = move_ghost(ghost_y, ghost_x, direction);
            // if we try all the directions, bail out - we can't move
        } while (move_result != MOVED_OKAY &&
                 (!tried_directions[0] || !tried_directions[1] || !tried_directions[2] || !tried_directions[3]));
    } else if (direction != EATING_PLAYER) {
        // if the ghost does see the player (but is not eating them), move in that direction
        move_ghost(ghost_y, ghost_x, direction);
    }
}
