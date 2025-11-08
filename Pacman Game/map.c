// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#include <stdio.h>
#include <stdlib.h>

#include "defines.h"
#include "colours.h"
#include "map.h"
#define IS_WALL 1
#define NOT_WALL 0

extern char *map, *dot_map;
extern int width, height;

/**
 * You should use this function to print out individual characters
 * in the colours used in the demo.
 * @param c
 */
static void printc(char c) {
    switch (c) {
        case WALL:
            change_text_colour(BLUE);
            break;
        case GHOST:
            change_text_colour(PINK);
            break;
        case PLAYER:
            change_text_colour(YELLOW);
            break;
        case DOT:
            change_text_colour(WHITE);
            break;
        default:
            change_text_colour(WHITE);
    }
    printf("%c", c);
}



char *load_map(char *filename, int *map_height, int *map_width) {
    FILE *fp = fopen(filename, "r"); // open file
    if (fp == NULL) { // error handling
        return NULL;
    }

    char line[1024]; // provides buffer for storage
    int width = 0;
    int height = 0;

    if (fgets(line, sizeof(line), fp)) { // gets width of line from first line in file
        int len = 0;

        while (line[len] != '\0'&& line[len] != '\n') {
            len++;
        }

        width = (2 + len) /3; // accounts for spaces in between characters in txt file
        height = 1;

    }
    while (fgets(line, sizeof(line), fp)) { //count remaining lines in file to get height
        height++;
    }

    *map_height = height;
    *map_width = width;

    map = malloc(width *height); // allocate memory as needed for map
    if (map == NULL) {
        return NULL;
    }

    rewind(fp); // go back to top of map, finally reading data, above code was to determine size

    //read each line (row) of the map
    for (int row = 0; row < height; row++) {
        if (!fgets(line, sizeof(line), fp)) {
            break;
        }
        for (int col = 0; col < width; col++) { // read each column of map
            int pos = col * 3; // accounts for spacing of characters in map.txt
            if (line[pos] == '\0' || line[pos] == '\n') {
                map[row * width + col] = EMPTY; // if empty, leave empty
            } else {
                map[row * width + col] = line[pos]; // otherwise
            }
        }
    }
    fclose(fp);
    return map;


}

void print_map(void) {
    for (int i = -1; i <= height; i++) {
        for (int j = -1; j <= width; j++) {
            // use is_wall to check borders
            if (j == -1 || j == width || i == -1 || i == height) {
                printc(WALL);
            } else {
                printc(map[j + i * width]);
            }
            printf(" ");
        }
        printf("\n");
    }
}


void find_ghosts(int ghosts_y[], int ghosts_x[]) {
    int found = 0; // counter var for num of ghosts found
    for (int y_pos = 0; y_pos < height && found < NUM_GHOSTS; y_pos++) {

        for (int x_pos = 0; x_pos < width && found < NUM_GHOSTS; x_pos++) {

            if (map[y_pos * width + x_pos] == GHOST) {
                ghosts_y[found] = y_pos; // save y pos
                ghosts_x[found] = x_pos; // save x pos
                found++;
            }
        }
    }
}

int is_wall(int y, int x) { // checks if (x,y) is a wall or out of bounds
    if (x < 0 || x >= width || y < 0 || y >= height) {
        return IS_WALL; // treated as wall
    }
    return (map[y * width + x] == WALL) ? IS_WALL : NOT_WALL;
}

void find_player(int *player_y, int *player_x) {
    for (int y_pos = 0; y_pos < height; y_pos++) {

        for (int x_pos = 0; x_pos < width; x_pos++) {

            if (map[y_pos * width + x_pos] == PLAYER) {
                *player_y = y_pos; // save y pos
                *player_x = x_pos; // save x pos
                return;
            }
        }
    }
}

