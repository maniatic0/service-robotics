#pragma once
#ifndef PATH_H
#define PATH_H

#define LEFTS 1
#define RIGHTS 2
#define LEFTS_CROSS 3
#define RIGHTS_CROSS 4

#define FORWARD 0
#define LEFT_CORNER (LEFTS)
#define RIGHT_CORNER (RIGHTS)
#define LEFT_T (LEFTS)
#define RIGHT_T (RIGHTS)
#define LEFT_WEIRD (LEFTS_CROSS)
#define RIGHT_WEIRD (RIGHTS_CROSS)
#define LEFT_CROSS (LEFTS_CROSS)
#define RIGHT_CROSS (RIGHTS_CROSS)
#define TARGET 9
#define ENTRANCE 10
#define TURN 11
#define FULL_STOP 12
#define DELAY 13

#define PATH_LENGTH 4

extern int dir;
extern int path[];
extern int path_pos;

void updatePath();

void PathSetup();

#endif