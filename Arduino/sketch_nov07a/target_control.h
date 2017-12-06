#pragma once
#ifndef TARGET_H
#define TARGET_H

#include "configuration.h"
#include "lines.h"
#include "motors.h"
#include "button.h"
#include "speakers.h"
#include "control.h"
#include "path.h"
#include "path_control.h"

#define CLOSE_DISTANCE 30.0

void WaitToLower();

void Target();

void TargetPick();

#endif
