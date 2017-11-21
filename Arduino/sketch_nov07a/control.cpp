#include "control.h"

bool on_intersection = false;
bool entering_intersection = false;
bool exiting_intersection = false;
bool top_corner = false; // If we are on top of a top_corner afer hitting the right right sensor
bool white_corner = false; // for cross intersections
bool black_corner = false; // for cross intersections
bool second_white_corner = false; // for cross intersections