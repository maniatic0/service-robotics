#include "path.h"

/*int path[PATH_LENGTH] = {LEFT_CORNER, LEFT_CROSS, FULL_STOP};*/
/*
int path[PATH_LENGTH] = {LEFT_CORNER, RIGHT_CORNER, FULL_STOP};*/

/*
int path[PATH_LENGTH] = {LEFT_CORNER, RIGHT_CORNER,
    RIGHT_T,LEFT_CORNER,
    RIGHT_T,RIGHT_CORNER,
    RIGHT_CORNER,LEFT_CORNER,
    LEFT_CORNER,LEFT_CORNER,
    LEFT_CORNER,RIGHT_CORNER,
    RIGHT_CORNER, FULL_STOP};*/

/*int path[PATH_LENGTH] = {LEFT_CORNER,RIGHT_CORNER,
    LEFT_T,RIGHT_CROSS,
    RIGHT_CORNER,RIGHT_CORNER,
    LEFT_CORNER,LEFT_CORNER,
    FORWARD,RIGHT_CORNER,
    LEFT_CORNER,LEFT_CORNER,TARGET,TURN,FULL_STOP};*/

int dir = LEFT_CORNER;
int path[PATH_LENGTH] = {TARGET, TURN, FULL_STOP};
int path_pos = 0;

void updatePath() {
    path_pos++;
    if (path_pos >= PATH_LENGTH)  path_pos = 0;
    dir = path[path_pos];
}

void PathSetup() {
	dir = path[path_pos];
}