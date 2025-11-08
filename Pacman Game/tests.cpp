
// APSC 142 Engineering Programming Project Starter Code
// Copyright Sean Kauffman 2024

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <stdio.h>

// make sure not to modify anything in this extern block
extern "C"{
#include "defines.h"
#include "map.h"
#include "actor.h"
#include "game.h"
char *map = NULL, *dot_map = NULL;
int width, height;
}

/**
 * This file is where you should put your tests for your code.
 * Your code must have tests that execute at least 85% of the code in
 * required functions for you to get full marks for the project.
 * Make sure to check out the course videos on automated testing for
 * more information about how to write tests.
 */

/* tests for map.c */
TEST_SUITE_BEGIN("Map tests");

// tests for load_map
TEST_CASE("A test for load_map") {
    CHECK(0 == 0);
}

// tests for is_wall

TEST_SUITE_END();

/* tests for actor.c */
TEST_SUITE_BEGIN("Actor tests");


TEST_CASE("Testing check_loss") {
    int ghosts_y[NUM_GHOSTS] = {0,0};
    int ghosts_x[NUM_GHOSTS] = {1,1};
    CHECK(check_loss(1, 1, ghosts_y, ghosts_x) == KEEP_GOING);
    CHECK(check_loss(0, 0, ghosts_y, ghosts_x) == KEEP_GOING);
    CHECK(check_loss(1, 0, ghosts_y, ghosts_x) == KEEP_GOING);
    CHECK(check_loss(0, 1, ghosts_y, ghosts_x) == YOU_LOSE);


}

// tests for sees_player

// tests for move_player

// tests for move_ghost

TEST_SUITE_END();

/* tests for game.c */
TEST_SUITE_BEGIN("Player movement tests");

//MOVE PLAYER RIGHT INTO A ___ SPACE
TEST_CASE("Test for move_player right into a dot") {

    int player_x = 0;
    int player_y = 0;

    //create a new map to simulate the game


    char tinyDotMap[] = {EMPTY, DOT,
                         DOT, DOT};
    char direction = RIGHT;

    map = tinyDotMap;
    dot_map = tinyDotMap;

    height = 2;
    width = 2;



    CHECK((move_player(&player_y, &player_x, direction) == MOVED_OKAY));
    CHECK(dot_map[1] == EMPTY);
}


TEST_CASE("Test for move_player right into a wall") { //wrong for some reason

    int player_x = 0;
    int player_y = 0;

    //create a new map to simulate the game


    char tinyDotMap[] = {EMPTY, WALL,
                         WALL, WALL};
    char direction = RIGHT;

    dot_map = tinyDotMap;

    height = 2;
    width = 2;



    CHECK((move_player(&player_y, &player_x, direction) == MOVED_WALL));


}

TEST_CASE("Test for move_player right into an empty space") {

    int player_x = 0;
    int player_y = 0;

    //create a new map to simulate the game


    char tinyDotMap[] = {DOT, DOT,
                         EMPTY, EMPTY};
    char direction = RIGHT;

    map = tinyDotMap;
    dot_map = tinyDotMap;

    height = 2;
    width = 2;



    CHECK((move_player(&player_y, &player_x, direction) == MOVED_OKAY));
    CHECK(dot_map[3] == EMPTY);

}

//MOVE PLAYER LEFT INTO A ___ SPACE
TEST_CASE("Test for move_player left into a dot") {

    int player_x = 1;
    int player_y = 0;

    //create a new map to simulate the game
    char tinyDotMap[] = {DOT, EMPTY,
                         DOT, WALL};
    char direction = LEFT;

    map = tinyDotMap;
    dot_map = tinyDotMap;

    height = 2;
    width = 2;



    CHECK((move_player(&player_y, &player_x, direction) == MOVED_OKAY));
    CHECK(dot_map[0] == EMPTY);
}


TEST_CASE("Test for move_player left into a wall") { //wrong

    int player_x = 1;
    int player_y = 0;

    //create a new map to simulate the game


    char tinyDotMap[] = {WALL, EMPTY,
                         WALL, WALL};
    char direction = LEFT;

    dot_map = tinyDotMap;

    height = 2;
    width = 2;



    CHECK((move_player(&player_y, &player_x, direction) == MOVED_WALL));
}

TEST_CASE("Test for move_player left into an empty space") {

    int player_x = 1;
    int player_y = 0;

    //create a new map to simulate the game

    char tinyDotMap[] = {EMPTY, EMPTY,
                         DOT, WALL};
    char direction = RIGHT;

    map = tinyDotMap;
    dot_map = tinyDotMap;

    height = 2;
    width = 2;



    CHECK((move_player(&player_y, &player_x, direction) == MOVED_OKAY));
    CHECK(dot_map[0] == EMPTY);

}


//MOVE PLAYER UP INTO A ___ SPACE
TEST_CASE("Test for move_player up into a dot") {

    int player_x = 0;
    int player_y = 1;

    //create a new map to simulate the game
    char tinyDotMap[] = {DOT, EMPTY,
                         DOT, WALL};
    char direction = UP;

    map = tinyDotMap;
    dot_map = tinyDotMap;

    height = 2;
    width = 2;



    CHECK((move_player(&player_y, &player_x, direction) == MOVED_OKAY));
    CHECK(dot_map[0] == EMPTY);
}


TEST_CASE("Test for move_player up into a wall") {

    int player_x = 0;
    int player_y = 1;

    //create a new map to simulate the game


    char tinyDotMap[] = {WALL, EMPTY,
                         PLAYER, DOT};
    char direction = UP;

    dot_map = tinyDotMap;

    height = 2;
    width = 2;



    CHECK((move_player(&player_y, &player_x, direction) == MOVED_WALL));
}

TEST_CASE("Test for move_player down into an empty space") {

    int player_x = 1;
    int player_y = 0;

    //create a new map to simulate the game

    char tinyDotMap[] = {EMPTY, EMPTY,
                         PLAYER, WALL};
    char direction = DOWN;

    map = tinyDotMap;
    dot_map = tinyDotMap;

    height = 2;
    width = 2;



    CHECK((move_player(&player_y, &player_x, direction) == MOVED_OKAY));
    CHECK(dot_map[0] == EMPTY);

}

//MOVE PLAYER UP INTO A ___ SPACE
TEST_CASE("Test for move_player down into a dot") {

    int player_x = 0;
    int player_y = 1;

    //create a new map to simulate the game
    char tinyDotMap[] = {DOT, EMPTY,
                         DOT, WALL};
    char direction = DOWN;

    map = tinyDotMap;
    dot_map = tinyDotMap;

    height = 2;
    width = 2;



    CHECK((move_player(&player_y, &player_x, direction) == MOVED_OKAY));
    CHECK(dot_map[0] == EMPTY);
}


TEST_CASE("Test for move_player DOWN into a wall") {

    int player_x = 0;
    int player_y = 0;

    //create a new map to simulate the game


    char tinyDotMap[] = {PLAYER, EMPTY,
                         WALL, DOT};
    char direction = DOWN;

    dot_map = tinyDotMap;

    height = 2;
    width = 2;



    CHECK((move_player(&player_y, &player_x, direction) == MOVED_WALL));
}

TEST_CASE("Test for move_player UP into an empty space") {

    int player_x = 0;
    int player_y = 1;

    //create a new map to simulate the game

    char tinyDotMap[] = {EMPTY, EMPTY,
                         PLAYER, WALL};
    char direction = UP;

    map = tinyDotMap;
    dot_map = tinyDotMap;

    height = 2;
    width = 2;



    CHECK((move_player(&player_y, &player_x, direction) == MOVED_OKAY));
    CHECK(dot_map[0] == EMPTY);

}


// tests for check_win

TEST_CASE("Test check_win") {


    //create a new map to simulate the game
    char tinyDotMap[] = {PLAYER, EMPTY,
                         EMPTY, WALL};

    char tinyDotMap2[] = {PLAYER, DOT,
                          DOT, WALL};

    dot_map = tinyDotMap;

    CHECK(check_win() == YOU_WIN);


    dot_map = tinyDotMap2;



    CHECK(check_win() == YOU_WIN);

}

TEST_CASE("Test invalid direction") {

    int player_x = 0;
    int player_y = 0;


    //create a new map to simulate the game
    char tinyDotMap[] = {PLAYER, EMPTY,
                         EMPTY, WALL};


    dot_map = tinyDotMap;

    CHECK(move_player(&player_x, &player_y, 'g') == MOVED_INVALID_DIRECTION);

}
/******************************************************************************************
 *
 *
 * ************************************************************************************/
TEST_SUITE_BEGIN("Ghost tests");

TEST_CASE("Ghost 1 has same coordinates as player") {
    int ghosts_y[NUM_GHOSTS] = {1,5};
    int ghosts_x[NUM_GHOSTS] = {1,5};

    int playerX = 1;
    int playerY = 1;

    CHECK(check_loss(playerY, playerX, ghosts_y, ghosts_x) == YOU_LOSE);

}

TEST_CASE("Ghost 2 has same coordinates as player") {
    int ghosts_y[NUM_GHOSTS] = {1,4};
    int ghosts_x[NUM_GHOSTS] = {1,4};

    int playerX = 4;
    int playerY = 4;

    CHECK(check_loss(playerY, playerX, ghosts_y, ghosts_x) == YOU_LOSE);

}


TEST_CASE("Both ghosts have same coordinates as player") {
    int ghosts_y[NUM_GHOSTS] = {4,4};
    int ghosts_x[NUM_GHOSTS] = {4,4};

    int playerX = 4;
    int playerY = 4;

    CHECK(check_loss(playerY, playerX, ghosts_y, ghosts_x) == YOU_LOSE);

}

TEST_CASE("No ghosts have same coordinates as player") {
    int ghosts_y[NUM_GHOSTS] = {1,4};
    int ghosts_x[NUM_GHOSTS] = {3,2};

    int playerX = 0;
    int playerY = 0;

    CHECK(check_loss(playerY, playerX, ghosts_y, ghosts_x) == KEEP_GOING);

}

TEST_CASE("move ghost covers all directions, covering dots, empties, walls") {
    int width = 3;
    int height = 3;
    int ghostX = 1;
    int ghostY = 1;

    //create a map and a dotmap
    map = (char*)malloc(width * height);
    dot_map = (char*)malloc(width * height);

    for(int i = 0; i < width * height; i++) {
        dot_map[i] = DOT;
        map[i] = DOT;
    }


    //invalid direction
    map[ghostY * width + ghostX] = GHOST;
    CHECK(move_ghost(&ghostY, &ghostX, 't') == MOVED_INVALID_DIRECTION);

    //test the boundaries
    ghostX = 0; ghostY = 0;
    map[ghostY * width + ghostX] = GHOST;
    CHECK(move_ghost(&ghostY, &ghostX, UP) == MOVED_WALL);
    CHECK(move_ghost(&ghostY, &ghostX, LEFT) == MOVED_WALL);
    ghostX = 1; ghostY = 1;

    //test walls that arent boundaries
    map[0 * width + 1] = WALL;
    CHECK(move_ghost(&ghostY, &ghostX, UP) == MOVED_WALL);
    map[0 * width + 1] = DOT;

    //dot restoration
    map[ghostY * width + ghostX] = GHOST;
    dot_map[ghostY * width + ghostX] = DOT;
    CHECK(move_ghost(&ghostY, &ghostX, RIGHT) == MOVED_OKAY);
    CHECK(map[1 * width + 1] == DOT);//check original position

    //check valid moves
    ghostX = 1; ghostY = 1;
    map[ghostY * width + ghostX] = GHOST;
    CHECK(move_ghost(&ghostY, &ghostX, DOWN) == MOVED_OKAY);

    ghostX = 1; ghostY = 1;
    map[ghostY * width + ghostX] = GHOST;
    CHECK(move_ghost(&ghostY, &ghostX, LEFT) == MOVED_OKAY);

    ghostX = 1; ghostY = 1;
    map[ghostY * width + ghostX] = GHOST;
    CHECK(move_ghost(&ghostY, &ghostX, RIGHT) == MOVED_OKAY);

    ghostX = 1; ghostY = 1;
    map[(ghostY-1) * width + ghostX] = EMPTY;
    map[ghostY * width + ghostX] = GHOST;
    CHECK(move_ghost(&ghostY, &ghostX, UP) == MOVED_OKAY);
}

TEST_CASE("sees_player") {

    width = 7;
    height = 7;
    map = (char*)malloc(width * height);


    for (int i = 0; i < width * height; i++) {
        map[i] = EMPTY;
    }


    //player is visible left, right, down, up
    CHECK(sees_player(1, 3, 5, 3) == UP);//player above ghost
    CHECK(sees_player(6, 3, 2, 3) == DOWN);//player below ghost
    CHECK(sees_player(3, 0, 3, 4) == LEFT);//player to ghost's left
    CHECK(sees_player(3, 6, 3, 2) == RIGHT);//player to ghost's right

    //player and ghost are same position
    CHECK(sees_player(3, 3, 3, 3) == EATING_PLAYER);

    //on a diagonal (ghost cannot see player)
    CHECK(sees_player(1, 1, 4, 4) == SEES_NOTHING);

    //wall obstructs ghost and player
    map[3 * width + 4] = WALL;  // Place wall at (3,4)
    CHECK(sees_player(3, 6, 3, 2) == SEES_NOTHING);


}

TEST_CASE("is_wall") {


    //test non wall areas
    CHECK(is_wall(0, 0) == 1);  // GHOST
    CHECK(is_wall(0, 1) == 1);  // DOT
    CHECK(is_wall(0, 2) == 1);  // PLAYER
    CHECK(is_wall(2, 2) == 1);  // EMPTY


    CHECK(is_wall(1, 1) == 1);  //wall

    // Test out-of-bounds
    CHECK(is_wall(-1, 0) == 1);  //above from top
    CHECK(is_wall(0, -1) == 1);  //from left from left edge
    CHECK(is_wall(0, 3) == 1);   //right from the right edge
    CHECK(is_wall(3, 0) == 1);   //from bottom
}


TEST_CASE("laod_map test") {
    CHECK(0 == 0);
}

TEST_CASE("final char is a dot"){
    int width = 0;
    int height = 0;
    char *loaded_map = load_map((char* ) "map.txt", &height, &width);


    CHECK(loaded_map[height*width-1] == DOT);

    free(loaded_map);
}

TEST_CASE("second char is a player"){
    int width = 0;
    int height = 0;
    char *loaded_map = load_map((char* ) "map.txt", &height, &width);


    CHECK(loaded_map[2*9+2] == PLAYER);

    free(loaded_map);
}

TEST_CASE("first char is a dot"){
    int width = 0;
    int height = 0;
    char *loaded_map = load_map((char* ) "map.txt", &height, &width);

    CHECK(loaded_map[0] == DOT);

    free(loaded_map);
}

TEST_SUITE_END();