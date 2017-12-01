#include "path.h"

int target1[TARGET1] = {LEFT_CORNER, RIGHT_CORNER,
    RIGHT_T,LEFT_CORNER,
    LEFT_T, TARGET,
    TURN};

/*starting on target1*/
int target2[TARGET2] = {RIGHT_WEIRD,RIGHT_CORNER,
    FORWARD,
/*After coming back of target one.
If this target was the first one we only had to start with:
LEFT_CORNER, RIGHT_CORNER,
LEFT_T,
and the rest was the same*/
    RIGHT_CROSS,RIGHT_CORNER,
    RIGHT_CORNER,LEFT_CORNER,
    LEFT_CORNER,FORWARD,
    RIGHT_CORNER,LEFT_CORNER,
    LEFT_CORNER,TARGET,
    TURN};

/*starting on target2*/
int target3[TARGET3] = {RIGHT_CORNER,RIGHT_CORNER,
    LEFT_CORNER,FORWARD,
    RIGHT_CORNER,RIGHT_CORNER,
    LEFT_CORNER,LEFT_CORNER,
    RIGHT_CROSS,
/*After coming back of target2.
If this target was the first one we only had to start with:
LEFT_CORNER, RIGHT_CORNER,
LEFT_T, FORWARD,
and the rest was the same*/
    RIGHT_CORNER, TARGET,
    TURN};

/*Entrance returning from target3*/
int exit_path[EXIT] = {LEFT_CORNER, FORWARD,
    RIGHT_WEIRD, LEFT_CORNER,
    RIGHT_CORNER, FULL_STOP};

int dir = LEFT_CORNER;
int path[PATH_LENGTH] = {LEFT_CORNER, RIGHT_CORNER,
    RIGHT_T,LEFT_CORNER,
    LEFT_T, TARGET,
    TURN,
    FORWARD, TARGET,
    TURN,
    FORWARD, TARGET,
    TURN,
    FULL_STOP};

int path_control_length[PATHS_AMOUNT] = {TARGET1, TARGET2, TARGET3, EXIT};
int* path_control[PATHS_AMOUNT] = {target1, target2, target3, exit_path};
int path_control_index = 0;

int path_pos = 0;

void updatePath() {
    path_pos++;
    //if (path_pos >= PATH_LENGTH)  path_pos = 0;
    //dir = path[path_pos];
    if (path_pos >= path_control_length[path_control_index]) {
      path_pos = 0;
      path_control_index++;
    }
    dir = path_control[path_control_index][path_pos];
}

void PathSetup() {
	dir = path_control[path_control_index][path_pos];
}
