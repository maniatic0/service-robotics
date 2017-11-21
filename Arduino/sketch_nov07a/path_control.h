#pragma once
#ifndef PATH_CONTROL_H
#define PATH_CONTROL_H


#include "Timer.h"

#include "configuration.h"
#include "line_control.h"
#include "lines.h"
#include "motors.h"
#include "path.h"
#include "control.h"

extern Timer timer;

void NormalLineControl();

void Forward();

void LeftS();

void RightS();

void LeftSCross();

void RightSCross();

//we want to turn 180 degrees for our left
void Turn();

void DelayAfter();

void Delay();

#endif